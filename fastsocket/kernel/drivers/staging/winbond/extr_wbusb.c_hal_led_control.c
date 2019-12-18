#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct wb35_reg {int U1BC_LEDConfigure; } ;
struct hw_data {int SoftwareSet; int LED_control; int LED_Blinking; scalar_t__ NullPacketCount; int time_count; TYPE_1__ LEDTimer; scalar_t__ LED_LinkOn; int /*<<< orphan*/  TxByteCountLast; int /*<<< orphan*/  RxByteCountLast; int /*<<< orphan*/  LED_Scanning; scalar_t__ CurrentRadioHw; scalar_t__ CurrentRadioSw; scalar_t__ SurpriseRemove; struct wb35_reg reg; } ;
struct wbsoft_priv {int /*<<< orphan*/  TxByteCount; int /*<<< orphan*/  RxByteCount; struct hw_data sHwData; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_NULL_PACKET_COUNT ; 
 int HAL_LED_SET_MASK ; 
 int HAL_LED_SET_SHIFT ; 
 int* LED_GRAY ; 
 int* LED_GRAY2 ; 
 int /*<<< orphan*/  Wb35Reg_Write (struct hw_data*,int,int) ; 
 int /*<<< orphan*/  Wb35Tx_CurrentTime (struct wbsoft_priv*,int) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static void hal_led_control(unsigned long data)
{
	struct wbsoft_priv *adapter = (struct wbsoft_priv *)data;
	struct hw_data *pHwData = &adapter->sHwData;
	struct wb35_reg *reg = &pHwData->reg;
	u32 LEDSet = (pHwData->SoftwareSet & HAL_LED_SET_MASK) >> HAL_LED_SET_SHIFT;
	u32 TimeInterval = 500, ltmp, ltmp2;
	ltmp = 0;

	if (pHwData->SurpriseRemove)
		return;

	if (pHwData->LED_control) {
		ltmp2 = pHwData->LED_control & 0xff;
		if (ltmp2 == 5)	// 5 is WPS mode
		{
			TimeInterval = 100;
			ltmp2 = (pHwData->LED_control >> 8) & 0xff;
			switch (ltmp2) {
			case 1:	// [0.2 On][0.1 Off]...
				pHwData->LED_Blinking %= 3;
				ltmp = 0x1010;	// Led 1 & 0 Green and Red
				if (pHwData->LED_Blinking == 2)	// Turn off
					ltmp = 0;
				break;
			case 2:	// [0.1 On][0.1 Off]...
				pHwData->LED_Blinking %= 2;
				ltmp = 0x0010;	// Led 0 red color
				if (pHwData->LED_Blinking)	// Turn off
					ltmp = 0;
				break;
			case 3:	// [0.1 On][0.1 Off][0.1 On][0.1 Off][0.1 On][0.1 Off][0.1 On][0.1 Off][0.1 On][0.1 Off][0.5 Off]...
				pHwData->LED_Blinking %= 15;
				ltmp = 0x0010;	// Led 0 red color
				if ((pHwData->LED_Blinking >= 9) || (pHwData->LED_Blinking % 2))	// Turn off 0.6 sec
					ltmp = 0;
				break;
			case 4:	// [300 On][ off ]
				ltmp = 0x1000;	// Led 1 Green color
				if (pHwData->LED_Blinking >= 3000)
					ltmp = 0;	// led maybe on after 300sec * 32bit counter overlap.
				break;
			}
			pHwData->LED_Blinking++;

			reg->U1BC_LEDConfigure = ltmp;
			if (LEDSet != 7)	// Only 111 mode has 2 LEDs on PCB.
			{
				reg->U1BC_LEDConfigure |= (ltmp & 0xff) << 8;	// Copy LED result to each LED control register
				reg->U1BC_LEDConfigure |= (ltmp & 0xff00) >> 8;
			}
			Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);
		}
	} else if (pHwData->CurrentRadioSw || pHwData->CurrentRadioHw)	// If radio off
	{
		if (reg->U1BC_LEDConfigure & 0x1010) {
			reg->U1BC_LEDConfigure &= ~0x1010;
			Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);
		}
	} else {
		switch (LEDSet) {
		case 4:	// [100] Only 1 Led be placed on PCB and use pin 21 of IC. Use LED_0 for showing
			if (!pHwData->LED_LinkOn)	// Blink only if not Link On
			{
				// Blinking if scanning is on progress
				if (pHwData->LED_Scanning) {
					if (pHwData->LED_Blinking == 0) {
						reg->U1BC_LEDConfigure |= 0x10;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 On
						pHwData->LED_Blinking = 1;
						TimeInterval = 300;
					} else {
						reg->U1BC_LEDConfigure &= ~0x10;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 Off
						pHwData->LED_Blinking = 0;
						TimeInterval = 300;
					}
				} else {
					//Turn Off LED_0
					if (reg->U1BC_LEDConfigure & 0x10) {
						reg->U1BC_LEDConfigure &= ~0x10;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 Off
					}
				}
			} else {
				// Turn On LED_0
				if ((reg->U1BC_LEDConfigure & 0x10) == 0) {
					reg->U1BC_LEDConfigure |= 0x10;
					Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 Off
				}
			}
			break;

		case 6:	// [110] Only 1 Led be placed on PCB and use pin 21 of IC. Use LED_0 for showing
			if (!pHwData->LED_LinkOn)	// Blink only if not Link On
			{
				// Blinking if scanning is on progress
				if (pHwData->LED_Scanning) {
					if (pHwData->LED_Blinking == 0) {
						reg->U1BC_LEDConfigure &= ~0xf;
						reg->U1BC_LEDConfigure |= 0x10;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 On
						pHwData->LED_Blinking = 1;
						TimeInterval = 300;
					} else {
						reg->U1BC_LEDConfigure &= ~0x1f;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 Off
						pHwData->LED_Blinking = 0;
						TimeInterval = 300;
					}
				} else {
					// 20060901 Gray blinking if in disconnect state and not scanning
					ltmp = reg->U1BC_LEDConfigure;
					reg->U1BC_LEDConfigure &= ~0x1f;
					if (LED_GRAY2[(pHwData->LED_Blinking % 30)]) {
						reg->U1BC_LEDConfigure |= 0x10;
						reg->U1BC_LEDConfigure |=
						    LED_GRAY2[(pHwData->LED_Blinking % 30)];
					}
					pHwData->LED_Blinking++;
					if (reg->U1BC_LEDConfigure != ltmp)
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 Off
					TimeInterval = 100;
				}
			} else {
				// Turn On LED_0
				if ((reg->U1BC_LEDConfigure & 0x10) == 0) {
					reg->U1BC_LEDConfigure |= 0x10;
					Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_0 Off
				}
			}
			break;

		case 5:	// [101] Only 1 Led be placed on PCB and use LED_1 for showing
			if (!pHwData->LED_LinkOn)	// Blink only if not Link On
			{
				// Blinking if scanning is on progress
				if (pHwData->LED_Scanning) {
					if (pHwData->LED_Blinking == 0) {
						reg->U1BC_LEDConfigure |=
						    0x1000;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_1 On
						pHwData->LED_Blinking = 1;
						TimeInterval = 300;
					} else {
						reg->U1BC_LEDConfigure &=
						    ~0x1000;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_1 Off
						pHwData->LED_Blinking = 0;
						TimeInterval = 300;
					}
				} else {
					//Turn Off LED_1
					if (reg->U1BC_LEDConfigure & 0x1000) {
						reg->U1BC_LEDConfigure &=
						    ~0x1000;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_1 Off
					}
				}
			} else {
				// Is transmitting/receiving ??
				if ((adapter->RxByteCount !=
				     pHwData->RxByteCountLast)
				    || (adapter->TxByteCount !=
					pHwData->TxByteCountLast)) {
					if ((reg->U1BC_LEDConfigure & 0x3000) !=
					    0x3000) {
						reg->U1BC_LEDConfigure |=
						    0x3000;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_1 On
					}
					// Update variable
					pHwData->RxByteCountLast =
					    adapter->RxByteCount;
					pHwData->TxByteCountLast =
					    adapter->TxByteCount;
					TimeInterval = 200;
				} else {
					// Turn On LED_1 and blinking if transmitting/receiving
					if ((reg->U1BC_LEDConfigure & 0x3000) !=
					    0x1000) {
						reg->U1BC_LEDConfigure &=
						    ~0x3000;
						reg->U1BC_LEDConfigure |=
						    0x1000;
						Wb35Reg_Write(pHwData, 0x03bc, reg->U1BC_LEDConfigure);	// LED_1 On
					}
				}
			}
			break;

		default:	// Default setting. 2 LED be placed on PCB. LED_0: Link On LED_1 Active
			if ((reg->U1BC_LEDConfigure & 0x3000) != 0x3000) {
				reg->U1BC_LEDConfigure |= 0x3000;	// LED_1 is always on and event enable
				Wb35Reg_Write(pHwData, 0x03bc,
					      reg->U1BC_LEDConfigure);
			}

			if (pHwData->LED_Blinking) {
				// Gray blinking
				reg->U1BC_LEDConfigure &= ~0x0f;
				reg->U1BC_LEDConfigure |= 0x10;
				reg->U1BC_LEDConfigure |=
				    LED_GRAY[(pHwData->LED_Blinking - 1) % 20];
				Wb35Reg_Write(pHwData, 0x03bc,
					      reg->U1BC_LEDConfigure);

				pHwData->LED_Blinking += 2;
				if (pHwData->LED_Blinking < 40)
					TimeInterval = 100;
				else {
					pHwData->LED_Blinking = 0;	// Stop blinking
					reg->U1BC_LEDConfigure &= ~0x0f;
					Wb35Reg_Write(pHwData, 0x03bc,
						      reg->U1BC_LEDConfigure);
				}
				break;
			}

			if (pHwData->LED_LinkOn) {
				if (!(reg->U1BC_LEDConfigure & 0x10))	// Check the LED_0
				{
					//Try to turn ON LED_0 after gray blinking
					reg->U1BC_LEDConfigure |= 0x10;
					pHwData->LED_Blinking = 1;	//Start blinking
					TimeInterval = 50;
				}
			} else {
				if (reg->U1BC_LEDConfigure & 0x10)	// Check the LED_0
				{
					reg->U1BC_LEDConfigure &= ~0x10;
					Wb35Reg_Write(pHwData, 0x03bc,
						      reg->U1BC_LEDConfigure);
				}
			}
			break;
		}

		//20060828.1 Active send null packet to avoid AP disconnect
		if (pHwData->LED_LinkOn) {
			pHwData->NullPacketCount += TimeInterval;
			if (pHwData->NullPacketCount >=
			    DEFAULT_NULL_PACKET_COUNT) {
				pHwData->NullPacketCount = 0;
			}
		}
	}

	pHwData->time_count += TimeInterval;
	Wb35Tx_CurrentTime(adapter, pHwData->time_count);	// 20060928 add
	pHwData->LEDTimer.expires = jiffies + msecs_to_jiffies(TimeInterval);
	add_timer(&pHwData->LEDTimer);
}