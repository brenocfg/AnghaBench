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
typedef  int u8 ;
struct pcf50633 {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  dump ;

/* Variables and functions */
#define  PCF50633_REG_INT1 132 
#define  PCF50633_REG_INT2 131 
#define  PCF50633_REG_INT3 130 
#define  PCF50633_REG_INT4 129 
#define  PCF50633_REG_INT5 128 
 struct pcf50633* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hex_dump_to_buffer (int*,int,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int pcf50633_reg_read (struct pcf50633*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t show_dump_regs(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct pcf50633 *pcf = dev_get_drvdata(dev);
	u8 dump[16];
	int n, n1, idx = 0;
	char *buf1 = buf;
	static u8 address_no_read[] = { /* must be ascending */
		PCF50633_REG_INT1,
		PCF50633_REG_INT2,
		PCF50633_REG_INT3,
		PCF50633_REG_INT4,
		PCF50633_REG_INT5,
		0 /* terminator */
	};

	for (n = 0; n < 256; n += sizeof(dump)) {
		for (n1 = 0; n1 < sizeof(dump); n1++)
			if (n == address_no_read[idx]) {
				idx++;
				dump[n1] = 0x00;
			} else
				dump[n1] = pcf50633_reg_read(pcf, n + n1);

		hex_dump_to_buffer(dump, sizeof(dump), 16, 1, buf1, 128, 0);
		buf1 += strlen(buf1);
		*buf1++ = '\n';
		*buf1 = '\0';
	}

	return buf1 - buf;
}