#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;

/* Variables and functions */
 int DMALEN ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finishDma () ; 
 int /*<<< orphan*/  lcdIfaceInit () ; 
 int* malloc (int) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sendRecvBufDma (int*,int*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void tskLcd(void *pvParameters)
{
    uint16_t *sbuf = malloc(DMALEN * 2);
    uint16_t *rbuf = malloc(DMALEN * 2);
    uint16_t xorval = 0;
    int x;
    lcdIfaceInit();
//  lcdFlush();
    while (1) {
        for (x = 0; x < DMALEN; x++) {
            sbuf[x] = x ^ xorval;
        }
        for (x = 0; x < DMALEN; x++) {
            rbuf[x] = 0;    //clear rbuf
        }
        sendRecvBufDma(sbuf, rbuf, DMALEN);
        vTaskDelay(20 / portTICK_PERIOD_MS);
        finishDma();
        for (x = 0; x < DMALEN; x++) if (rbuf[x] != (x ^ xorval)) {
                printf("Rxbuf err! pos %d val %x xor %x", x, (int)rbuf[x], (int)xorval);
            }
        printf(".");
        fflush(stdout);
        xorval++;
    }
}