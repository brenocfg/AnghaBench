#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct pbuf {scalar_t__ payload; } ;
struct TYPE_5__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  a; TYPE_1__ s; } ;
typedef  TYPE_3__ ledPacket_type ;
struct TYPE_6__ {int param1; int /*<<< orphan*/  payload; void* type; } ;
struct TYPE_8__ {int /*<<< orphan*/  a; TYPE_2__ s; } ;

/* Variables and functions */
 scalar_t__ BL_MODE_INACTIVE ; 
 int /*<<< orphan*/  BUTTONS_Config () ; 
 int BUTTONS_Read_All () ; 
 int /*<<< orphan*/  CONFIG_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGPIN_NUM ; 
 int /*<<< orphan*/  DEBUGPIN_TGL (int) ; 
 int /*<<< orphan*/  Delay (int) ; 
 int /*<<< orphan*/  ETH_BSP_Config () ; 
 scalar_t__ ETH_CheckFrameReceived () ; 
 int /*<<< orphan*/  IP4_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IP_ADDR0 ; 
 int /*<<< orphan*/  IP_ADDR1 ; 
 int /*<<< orphan*/  IP_ADDR2 ; 
 int IP_lastOctet ; 
 scalar_t__ LocalTime ; 
 int /*<<< orphan*/  LwIP_Init () ; 
 int /*<<< orphan*/  LwIP_Periodic_Handle (scalar_t__) ; 
 int /*<<< orphan*/  LwIP_Pkt_Handle () ; 
 int /*<<< orphan*/  NVIC_PriorityGroupConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_PriorityGroup_4 ; 
 size_t PANEL_NE ; 
 size_t PANEL_NW ; 
 size_t PANEL_SE ; 
 size_t PANEL_SW ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_TRANSPORT ; 
 int /*<<< orphan*/  PIN_Config () ; 
 int /*<<< orphan*/  PIN_Low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_Num (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PIN_State (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_TYPE_DOTCORRECT_PACK12 ; 
 void* PKT_TYPE_GSVALS ; 
 void* PKT_TYPE_SET_LOOKUP ; 
 int POWER_ROW ; 
 int /*<<< orphan*/  PWRCTRL_NUM_PINS ; 
 int /*<<< orphan*/  PWR_CTRL_AC_0 ; 
 int /*<<< orphan*/  PWR_CTRL_AC_1 ; 
 int /*<<< orphan*/  PWR_MON_0_0 ; 
 int /*<<< orphan*/  PWR_MON_0_1 ; 
 int /*<<< orphan*/  PWR_MON_0_2 ; 
 int /*<<< orphan*/  PWR_MON_1_0 ; 
 int /*<<< orphan*/  PWR_MON_1_1 ; 
 int /*<<< orphan*/  PWR_MON_1_2 ; 
 int /*<<< orphan*/  PWR_MON_AC_0 ; 
 int /*<<< orphan*/  PWR_MON_AC_1 ; 
 int /*<<< orphan*/  UART_Config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_SendBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USART_NE ; 
 int /*<<< orphan*/  USART_NW ; 
 int /*<<< orphan*/  USART_SE ; 
 int /*<<< orphan*/  USART_SW ; 
 scalar_t__ bootloaderMode ; 
 int /*<<< orphan*/  buttonpacket ; 
 int calcMedian (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fan_tach ; 
 int global_column ; 
 int /*<<< orphan*/  global_pcb ; 
 int global_row ; 
 int /*<<< orphan*/  handle_feedback (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ lastButtonPacketTime ; 
 scalar_t__ lastPacketTime ; 
 scalar_t__ lastStatusPacketTime ; 
 scalar_t__ lastUDPReceivePacketTime ; 
 TYPE_4__* ledpackets ; 
 int mac_last_octet ; 
 scalar_t__ maxPacketDelay ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ minButtonPacketDelay ; 
 scalar_t__ minPacketDelay ; 
 scalar_t__ minStatusPacketDelay ; 
 int /*<<< orphan*/  pack12bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * panelLEDmap ; 
 int /*<<< orphan*/  panel_avg_temp ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  pins_debug ; 
 int /*<<< orphan*/  pins_powerctrl ; 
 int pow (float,double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sendLEDpackets () ; 
 int /*<<< orphan*/  serialNum ; 
 int /*<<< orphan*/  temperatures ; 
 int /*<<< orphan*/  test_modes () ; 
 int /*<<< orphan*/  udp_dest ; 
 int /*<<< orphan*/  udp_recv_init () ; 
 int /*<<< orphan*/  udp_sendto (int /*<<< orphan*/ ,struct pbuf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uptimes ; 
 int /*<<< orphan*/ * usarts ; 

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured to
       168 MHz, this is done through SystemInit() function which is called from
       startup file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */
    int i;

    struct pbuf *p;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* configure ethernet (GPIOs, clocks, MAC, DMA) */
    printf("about to start ethernet config\n");
    ETH_BSP_Config();

    // Determine the IP address based on dip switch position
    BUTTONS_Config();
    PIN_Config();
    CONFIG_pins(pins_powerctrl, PWRCTRL_NUM_PINS);
    PIN_Num(pins_debug, 0, DEBUGPIN_NUM);

    PIN_Low(pins_powerctrl, PWR_CTRL_AC_0);
    PIN_Low(pins_powerctrl, PWR_CTRL_AC_1);

    Delay(10);
    i = BUTTONS_Read_All();
    #ifdef TEST_MODES
        i = 2;
    #endif
    global_row = (i >> 4) & 0xF;
    global_column = i & 0xF;
    IP_lastOctet = 20+global_row*10+global_column;
    mac_last_octet = 20+global_row*10+global_column;
    printf("IP: 192.168.0.%d", IP_lastOctet);

    IP4_ADDR(&udp_dest, IP_ADDR0, IP_ADDR1, IP_ADDR2, 10);

    /* Initilaize the LwIP stack */
    LwIP_Init();

    // Initialize, bind, and setup callback for UDP
    udp_recv_init();

    if(global_row != POWER_ROW) {
        // this is a normal panel (not a power box)
        UART_Config(&usarts[0]);
        UART_Config(&usarts[1]);
        UART_Config(&usarts[2]);
        UART_Config(&usarts[3]);

        Delay(10);

        //startBootloader();
        //doBootloaderTest();

        // Wait for initialization of LED board firmware and debug display
        Delay(7000);

        // run through sequence of setting dot correction
        int dotval = 58;
        while(dotval <= 63) {
            Delay(50);
            // set dot correction
            ledPacket_type pkt;
            memset(pkt.a, 0, sizeof(ledPacket_type));
            pkt.s.type = PKT_TYPE_DOTCORRECT_PACK12;
            for(i = 0; i < 49; i++) {
                pack12bit(pkt.s.payload, panelLEDmap[i*3+1], dotval);
                #ifdef TEST_MODES
                    pack12bit(pkt.s.payload, panelLEDmap[i*3], dotval*12/16);
                    pack12bit(pkt.s.payload, panelLEDmap[i*3+2], dotval*12/16);
                #else
                    pack12bit(pkt.s.payload, panelLEDmap[i*3  ], dotval/2);
                    pack12bit(pkt.s.payload, panelLEDmap[i*3+2], dotval/2);
                #endif
            }
            UART_SendBytes(&usarts[0], pkt.a, sizeof(ledPacket_type));
            UART_SendBytes(&usarts[1], pkt.a, sizeof(ledPacket_type));
            UART_SendBytes(&usarts[2], pkt.a, sizeof(ledPacket_type));
            UART_SendBytes(&usarts[3], pkt.a, sizeof(ledPacket_type));
            Delay(50);
            ledpackets[PANEL_NW].s.type = PKT_TYPE_GSVALS;
            for(i = 0; i <7*3; i++)
                pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[i], 800);
            for(; i <49*3; i++)
                pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[i], 0);
            UART_SendBytes(&usarts[3], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            UART_SendBytes(&usarts[2], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            UART_SendBytes(&usarts[1], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            UART_SendBytes(&usarts[0], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            dotval++;
            Delay(30);
        }
        // set calibration to a 2.2 gamma curve
        {
            int j;
            float value;
            uint16_t iValue;
            ledpackets[PANEL_NW].s.type = PKT_TYPE_SET_LOOKUP;
            for(i = 0; i < 65; i++) {
                value = 4000*pow( (float)i/65.0, 2.2);
                iValue = ((uint16_t)value) & 0xFFF;
                for(j = 0; j < 49*3; j++) {
                    pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[j], iValue);
                }
                ledpackets[PANEL_NW].s.param1 = i;
                UART_SendBytes(&usarts[3], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                UART_SendBytes(&usarts[2], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                UART_SendBytes(&usarts[1], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                UART_SendBytes(&usarts[0], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                Delay(30);
            }
        }
        // turn off all channels
        ledpackets[PANEL_NW].s.type = PKT_TYPE_GSVALS;
        for(i = 0; i <49*3; i++) {
            pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[i], 0);
        }
        UART_SendBytes(&usarts[3], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
        UART_SendBytes(&usarts[2], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
        UART_SendBytes(&usarts[1], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
        UART_SendBytes(&usarts[0], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));

        // Startup sequence that lights all the LEDs one at a time
        ledpackets[PANEL_NW].s.type = PKT_TYPE_GSVALS;
        for(i = 0; i <49*3+1; i++) {
            if(i < 49*3)
                pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[i], 800);
            if(i > 0)
                pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[i-1], 0);
            UART_SendBytes(&usarts[3], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            UART_SendBytes(&usarts[2], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            UART_SendBytes(&usarts[1], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
            UART_SendBytes(&usarts[0], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));

            Delay(10);
        }

        #ifdef TEST_MODES
            test_modes();
        #endif

        //buttonTest();
    }

    // Normal execution infinite while loop
    while(1) {
        if (ETH_CheckFrameReceived()) {
            /* process received ethernet packet*/
            LwIP_Pkt_Handle();
        }

        // for normal panels send packet to LED boards if overdue and not in bootloader mode
        if(global_row != POWER_ROW && LocalTime - lastPacketTime >= maxPacketDelay && bootloaderMode == BL_MODE_INACTIVE) {
            sendLEDpackets();
            DEBUGPIN_TGL(8);
        }

        if(global_row == POWER_ROW) {
            // This is a power box controller
            if(LocalTime-lastStatusPacketTime >= minStatusPacketDelay) {
                lastStatusPacketTime = LocalTime;
                p = pbuf_alloc(PBUF_TRANSPORT, 4+6+2+2, PBUF_RAM);
                i = 0;
                ((uint8_t*)p->payload)[i++] = 0x22;
                ((uint8_t*)p->payload)[i++] = 0x0;
                ((uint8_t*)p->payload)[i++] = 0x0;
                ((uint8_t*)p->payload)[i++] = 0x0;
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_MON_0_0);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_MON_0_1);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_MON_0_2);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_MON_1_0);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_MON_1_1);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_MON_1_2);
                ((uint8_t*)p->payload)[i++] = !PIN_State(pins_powerctrl, PWR_MON_AC_0);
                ((uint8_t*)p->payload)[i++] = !PIN_State(pins_powerctrl, PWR_MON_AC_1);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_CTRL_AC_0);
                ((uint8_t*)p->payload)[i++] = PIN_State(pins_powerctrl, PWR_CTRL_AC_1);
                udp_sendto(global_pcb, p, &udp_dest, 27482);
                /* free the pbuf */
                pbuf_free(p);
            }
        } else {
            // This is an LED panel controller

            // build and send button data packet at a fixed rate
            if(LocalTime-lastButtonPacketTime >= minButtonPacketDelay && bootloaderMode == BL_MODE_INACTIVE) {
                lastButtonPacketTime = LocalTime;
                DEBUGPIN_TGL(7);
                p = pbuf_alloc(PBUF_TRANSPORT, 29, PBUF_RAM);
                memcpy(p->payload, buttonpacket, 29);
                udp_sendto(global_pcb, p, &udp_dest, 27482);
                /* free the pbuf */
                pbuf_free(p);
            }
            // build and send button data packet at a fixed rate
            if(LocalTime-lastStatusPacketTime >= minStatusPacketDelay && bootloaderMode == BL_MODE_INACTIVE) {
                lastStatusPacketTime = LocalTime;
                p = pbuf_alloc(PBUF_TRANSPORT, 4+196+4+4*6+4*4+4, PBUF_RAM);
                ((uint8_t*)p->payload)[0] = 0x21;
                memcpy(p->payload+4, temperatures, 196);
                ((uint8_t*)(p->payload))[4+196+0] = calcMedian(fan_tach[0]);
                ((uint8_t*)(p->payload))[4+196+1] = calcMedian(fan_tach[1]);
                ((uint8_t*)(p->payload))[4+196+2] = calcMedian(fan_tach[2]);
                ((uint8_t*)(p->payload))[4+196+3] = calcMedian(fan_tach[3]);
                memcpy(p->payload+4+196+4, serialNum, 4*6);
                memcpy(p->payload+4+196+4+4*6, uptimes, 4*4);
                memcpy(p->payload+4+196+4+4*6+4*4, panel_avg_temp, 4);
                udp_sendto(global_pcb, p, &udp_dest, 27482);
                /* free the pbuf */
                pbuf_free(p);
            }
        }

        LwIP_Periodic_Handle(LocalTime);

        // Turn off the display if we don't receive anything for more than 5 seconds
        if( (LocalTime - lastUDPReceivePacketTime) > 5000 ) {
            // turn off all channels
            ledpackets[PANEL_NW].s.type = PKT_TYPE_GSVALS;
            for(i = 0; i <49*3; i++) {
                pack12bit(ledpackets[PANEL_NW].s.payload, panelLEDmap[i], 0);
            }
            if( (global_row != POWER_ROW) && (LocalTime - lastPacketTime >= minPacketDelay) ) {
                handle_feedback(USART_NW, PANEL_NW);
                handle_feedback(USART_SW, PANEL_SW);
                handle_feedback(USART_SE, PANEL_SE);
                handle_feedback(USART_NE, PANEL_NE);
                UART_SendBytes(&usarts[3], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                UART_SendBytes(&usarts[2], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                UART_SendBytes(&usarts[1], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                UART_SendBytes(&usarts[0], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
                lastPacketTime = LocalTime;
            }
        }
    }
}