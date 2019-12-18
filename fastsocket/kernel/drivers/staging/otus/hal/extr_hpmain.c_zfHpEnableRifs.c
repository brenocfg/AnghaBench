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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

void zfHpEnableRifs(zdev_t* dev, u8_t mode24g, u8_t modeHt, u8_t modeHt2040)
{

    /* # Enable Reset TDOMAIN
     * $rddata = &$phyreg_read(0x9800+(738<<2));
     * $wrdata = $rddata | (0x1 << 26) | (0x1 << 27);
     * &$phyreg_write(0x9800+(738<<2), $wrdata);
     */
    reg_write (0x9800+(738<<2), 0x08000000 | (0x1 << 26) | (0x1 << 27));
    //reg_write (0x9800+(738<<2), 0x08000000 | (0x1 << 26));

    /* # reg 123: heavy clip factor, xr / RIFS search parameters */
    reg_write (0x99ec, 0x0cc80caa);

    /* # Reduce Search Start Delay for RIFS    */
    if (modeHt == 1) /* ($HT_ENABLE == 1) */
    {
        if (modeHt2040 == 0x1) /* ($DYNAMIC_HT2040_EN == 0x1) */
        {
            reg_write(0x9800+(70<<2), 40);/*40*/
        }
        else
        {
            reg_write(0x9800+(70<<2), 20);
            if(mode24g == 0x0)
            {
                /* $rddata = &$phyreg_read(0x9800+(24<<2));#0x9860;0x1c5860
                 *$wrdata = ($rddata & 0xffffffc7) | (0x4 << 3);
                 * &$phyreg_write(0x9800+(24<<2), $wrdata);
                 */
                reg_write(0x9800+(24<<2), (0x0004dd10 & 0xffffffc7) | (0x4 << 3));
            }
        }
    }

    if (mode24g == 0x1)
    {
        reg_write(0x9850, 0xece8b4e4);/*org*/
        //reg_write(0x9850, 0xece8b4e2);
        reg_write(0x985c, 0x313a5d5e);
    }
    else
    {
        reg_write(0x9850, 0xede8b4e4);
        reg_write(0x985c, 0x3139605e);
    }

    zfFlushDelayWrite(dev);

    return;
}