#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ledPacket_type ;
struct TYPE_7__ {int* payload; int type; int /*<<< orphan*/  param1; } ;
struct TYPE_11__ {int* ua; TYPE_1__ s; int /*<<< orphan*/ * a; } ;
struct TYPE_8__ {int* payload; scalar_t__ type; } ;
struct TYPE_10__ {TYPE_2__ s; int /*<<< orphan*/ * a; } ;
struct TYPE_9__ {int HCLK_Frequency; } ;
typedef  TYPE_3__ RCC_ClocksTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ANALOG_Config () ; 
 int ANALOG_get_voltage (int /*<<< orphan*/ ) ; 
 int BLACK_TIMEOUT ; 
 int /*<<< orphan*/  BUTTONS_Config () ; 
 int BUTTONS_Read (int) ; 
 int CONFIG_get_addr () ; 
 int /*<<< orphan*/  DEBUGPIN_Config () ; 
 int /*<<< orphan*/  Delay (int) ; 
 int FanCapture ; 
 int FanLastIrq ; 
 int LED_PACKET_HEADER_LEN ; 
 int LocalTime ; 
 int* MACaddr ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
#define  PKT_TYPE_8BIT_CAL 136 
#define  PKT_TYPE_8BIT_RAW 135 
#define  PKT_TYPE_DOTCORRECT_PACK12 134 
#define  PKT_TYPE_DOTCORRECT_PACK6 133 
#define  PKT_TYPE_DOTCORRECT_PACK8 132 
#define  PKT_TYPE_GET_LOOKUP 131 
#define  PKT_TYPE_GSVALS 130 
#define  PKT_TYPE_REBOOT 129 
#define  PKT_TYPE_SET_LOOKUP 128 
 int /*<<< orphan*/  RCC_GetClocksFreq (TYPE_3__*) ; 
 scalar_t__ RESET ; 
 int SYSTEMTICK_PERIOD_MS ; 
 int /*<<< orphan*/  SysTick_CLKSourceConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysTick_CLKSource_HCLK ; 
 int /*<<< orphan*/  SysTick_Config (int) ; 
 int /*<<< orphan*/  SysTick_IRQn ; 
 int TICKS_PER_MS ; 
 int TLC59401_CHANNELS ; 
 int /*<<< orphan*/  TLC59401_Config () ; 
 int /*<<< orphan*/  TLC59401_GetCalibration (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TLC59401_Send () ; 
 int /*<<< orphan*/  TLC59401_SendDotCorrection () ; 
 int /*<<< orphan*/  TLC59401_Set8bitCalValue (int,int) ; 
 int /*<<< orphan*/  TLC59401_SetCalibration (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TLC59401_SetDotCorrection (int,void*) ; 
 int /*<<< orphan*/  TLC59401_SetDotCorrectionPacket (int*) ; 
 int /*<<< orphan*/  TLC59401_SetPacket (int*) ; 
 int /*<<< orphan*/  TLC59401_SetValue (int,int) ; 
 int /*<<< orphan*/  UART_Config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USART1 ; 
 int /*<<< orphan*/  USART_ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_FLAG_ORE ; 
 int /*<<< orphan*/  USART_FLAG_RXNE ; 
 int /*<<< orphan*/  USART_FLAG_TXE ; 
 scalar_t__ USART_GetFlagStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ReceiveData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_SendData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * analog_map ; 
 int busAddress ; 
 int /*<<< orphan*/  eeprom_Config () ; 
 int /*<<< orphan*/  eeprom_ReadMAC (int*) ; 
 void* fan_pwm ; 
 int /*<<< orphan*/  fan_set_duty (void*) ; 
 int /*<<< orphan*/  fan_setup () ; 
 TYPE_5__ inPacket ; 
 int lastByteTime ; 
 void* led_pwm ; 
 TYPE_4__ outPacket ; 
 int packetIdx ; 
 int packetStarted ; 
 void* unpack12bit (int*,int) ; 
 int /*<<< orphan*/ * usarts ; 
 int /*<<< orphan*/  usleep (int) ; 

int main(void) {
    int i;
    uint8_t inByte;
    int RXcount = 0;
    int TXcount = 0;
    int RX_overrun_clear_count = 0;

    RCC_ClocksTypeDef RCC_Clocks;

    LocalTime = 0;

    // set up systick
    /* Configure Systick clock source as HCLK */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    // do eeprom process before starting any interrupts due to time critical nature of bit-bang implementation and 6% timing error allowance
    busAddress = CONFIG_get_addr();
    if(busAddress == 0) {
        eeprom_Config();
        eeprom_ReadMAC(MACaddr);
    }

    // do analog setup before things get noisy
    usleep(100000); // give power a little time to stabilize
    ANALOG_Config();

    /* SystTick configuration: an interrupt every 1ms */
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / (1000/SYSTEMTICK_PERIOD_MS*TICKS_PER_MS));

    /* Set Systick interrupt priority to 0*/
    NVIC_SetPriority (SysTick_IRQn, 0);

    if(busAddress == 3)
        fan_setup();

    Delay(1000);

    DEBUGPIN_Config();

    BUTTONS_Config();

    TLC59401_Config();

    // test sequence
    for(i = 0; i < 32; i ++) {
        TLC59401_SetValue(i, 500);
        if(i > 0)
            TLC59401_SetValue(i-1, 0);
        TLC59401_Send();
        Delay(30);
    }
    TLC59401_SetValue(31, 0);
    TLC59401_Send();
    Delay(30);

    // display the bus address on the LEDs
    TLC59401_SetValue(2, 500);
    if(busAddress >= 1)
        TLC59401_SetValue(5, 500);
    if(busAddress >= 2)
        TLC59401_SetValue(8, 500);
    if(busAddress >= 3)
        TLC59401_SetValue(11, 500);
    if(busAddress >= 4)
        TLC59401_SetValue(14, 500);
    TLC59401_Send();
    Delay(30);

    UART_Config(&usarts[0]);
    while(1) {
        // Grab a serial packet
        while(1) {
            // wait for byte to be available while sending the LED packet
            while( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET ) {
                if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)) {
                    USART_ClearFlag(USART1,USART_FLAG_ORE);
                    RX_overrun_clear_count++;
                    packetStarted = false;
                }
                //if(lastByteTime+1 < LocalTime)
                if((LocalTime - lastByteTime) > TICKS_PER_MS)  // this should be timer wrap safe
                    packetStarted = false;
                if((LocalTime - lastByteTime) > (BLACK_TIMEOUT*TICKS_PER_MS)) {  // If we haven't received anything for 5 seconds turn off the LEDs
                    for(i=0; i < TLC59401_CHANNELS; i++)
                        TLC59401_SetValue(i, 0);
                    TLC59401_Send();
                }
            }
            inByte = USART_ReceiveData(USART1);
            RXcount++;
            if(!packetStarted) {
                if((LocalTime - lastByteTime) > TICKS_PER_MS) {
                    // more than a full millisecond has elapsed since our last byte so this is the start of a packet
                    packetStarted = true;
                    packetIdx = 0;
                } else {
                    // in the middle of a unsynchronized packet?
                    lastByteTime = LocalTime;
                    continue;
                }
            }
            outPacket.a[packetIdx++] = inByte;
            lastByteTime = LocalTime;
            if( packetIdx >= sizeof(ledPacket_type) ) {
                // we are done with this packet
                packetStarted = false;
                break;
            }
        }
        // copy contents intended for this device to the input packet
        for(i = 0; i < LED_PACKET_HEADER_LEN; i++) { // copy the header over
            inPacket.a[i] = outPacket.a[i];
        }
        for(i = 0; i < 48; i++)
            inPacket.s.payload[i] = outPacket.s.payload[i + busAddress*48];

        // Fill our portion of the outgoing packet
        if(inPacket.s.type == PKT_TYPE_GET_LOOKUP) {
            TLC59401_GetCalibration(inPacket.s.param1, outPacket.s.payload + busAddress*48);
        } else {
            uint32_t tempWork;
            // 0-10 update button status in outgoing packet
            for(i = 0; i < 10; i++)
                outPacket.s.payload[i + busAddress*48] = BUTTONS_Read(i);
            // 10-19 update thermistor values
            for(i = 0; i < 10; i++) {
                tempWork = ANALOG_get_voltage(analog_map[i]);
                // fixed point linear approximation math to convert to deg F (roughly accurate from 70-220 degrees)
                tempWork = (tempWork*2753+2066808) >> 16;
                outPacket.s.payload[i + 10 + busAddress*48] = tempWork;
            }
            // 20-25 addr==0: update MAC address in outgoing packet
            //       addr==3: update FAN Tach value
            if(busAddress == 0)
                for(i = 0; i < 6; i++)
                    outPacket.s.payload[i + 20 + busAddress*48] = MACaddr[i];
            if(busAddress == 3) {
                if( (LocalTime - FanLastIrq) > TICKS_PER_MS*1000 )
                    FanCapture = 0xFFFF;
                for(i = 0; i < 4; i++)
                    outPacket.s.payload[i + 20 + busAddress*48] = (FanCapture >> (24-8*i)) & 0xFF;
            }
            // 32-35 Uptime in ms/6
            tempWork = LocalTime; // copy for update safety
            for(i = 0; i < 4; i++)
                outPacket.s.payload[i + 32 + busAddress*48] = (tempWork >> (24-8*i)) & 0xFF;
        }

        // send outgoing packet
        for(i = 0; i < sizeof(ledPacket_type); i++) {
            while( USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET );
            USART_SendData(USART1, outPacket.a[i]);
            TXcount++;
        }
        if(outPacket.s.type != PKT_TYPE_SET_LOOKUP) {
            fan_pwm = unpack12bit(inPacket.ua+1, 0);
            if(busAddress == 3)
                fan_set_duty(fan_pwm);
            led_pwm = unpack12bit(inPacket.ua+1, 1);
        }

        // handle all the expected packet types
        switch(inPacket.s.type) {
            case PKT_TYPE_8BIT_CAL: // 1
                for(i = 0; i < TLC59401_CHANNELS; i++) {
                    TLC59401_Set8bitCalValue( i, inPacket.s.payload[i] );
                }
                TLC59401_Send();
                break;
            case PKT_TYPE_GSVALS: // 2
                // Update LED values
                TLC59401_SetPacket(inPacket.s.payload);
                // disable pixels to do three rail approximation
                /*if(busAddress == 3)
                    for(i=0; i < 32; i++)
                        TLC59401_SetValue(i, 0);
                if(busAddress == 2)
                    for(i=0; i < 12; i++)
                        TLC59401_SetValue(i, 0);
                if(busAddress == 4)
                    for(i=0; i < 12; i++)
                        TLC59401_SetValue(i, 0);*/
                TLC59401_Send();
                break;
            case PKT_TYPE_DOTCORRECT_PACK12: // 3
                // Update dot correction values with same bit alignment as greyscale data
                for(i = 0; i < 32; i++)
                    TLC59401_SetDotCorrection( i, unpack12bit(inPacket.s.payload,i) );
                TLC59401_SendDotCorrection();
                break;
            case PKT_TYPE_8BIT_RAW: // 4
                for(i = 0; i < TLC59401_CHANNELS; i++) {
                    TLC59401_SetValue( i, ((uint16_t)inPacket.s.payload[i]) << 4 );
                }
                TLC59401_Send();
                break;
            case PKT_TYPE_SET_LOOKUP: // 5
                TLC59401_SetCalibration(inPacket.s.param1, inPacket.s.payload);
                break;
            case PKT_TYPE_DOTCORRECT_PACK8: // 6
                for(i = 0; i < 32; i++)
                    TLC59401_SetDotCorrection( i, unpack12bit(inPacket.s.payload,i) );
                TLC59401_SendDotCorrection();
                break;
            case PKT_TYPE_DOTCORRECT_PACK6: // 7
                TLC59401_SetDotCorrectionPacket(inPacket.s.payload);
                TLC59401_SendDotCorrection();
                break;
            case PKT_TYPE_GET_LOOKUP: // 8
                // already taken care of
                break;
            case PKT_TYPE_REBOOT: // 0xF0
                {
                    uint32_t *inBuf = (uint32_t *)inPacket.s.payload;
                    if(inBuf[0] == 0x816A4EB2) {
                        Delay(100*TICKS_PER_MS);  // delay 100ms before rebooting to make sure outgoing packet gets sent completely
                        NVIC_SystemReset();
                    }
                }
                break;
            default:
                break;
        }
    }
}