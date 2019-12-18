#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_char ;
struct sym_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; int byte_count; int checksum; int /*<<< orphan*/  trailer; } ;
typedef  TYPE_1__ Symbios_nvram ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBIOS_NVRAM_ADDRESS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ sym_read_S24C16_nvram (struct sym_device*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int sym_read_Symbios_nvram(struct sym_device *np, Symbios_nvram *nvram)
{
	static u_char Symbios_trailer[6] = {0xfe, 0xfe, 0, 0, 0, 0};
	u_char *data = (u_char *) nvram;
	int len  = sizeof(*nvram);
	u_short	csum;
	int x;

	/* probe the 24c16 and read the SYMBIOS 24c16 area */
	if (sym_read_S24C16_nvram (np, SYMBIOS_NVRAM_ADDRESS, data, len))
		return 1;

	/* check valid NVRAM signature, verify byte count and checksum */
	if (nvram->type != 0 ||
	    memcmp(nvram->trailer, Symbios_trailer, 6) ||
	    nvram->byte_count != len - 12)
		return 1;

	/* verify checksum */
	for (x = 6, csum = 0; x < len - 6; x++)
		csum += data[x];
	if (csum != nvram->checksum)
		return 1;

	return 0;
}