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
struct pcmcia_device {char** prod_id; } ;
struct TYPE_3__ {char serial; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void ixj_get_serial(struct pcmcia_device * link, IXJ * j)
{
	char *str;
	int i, place;
	DEBUG(0, "ixj_get_serial(0x%p)\n", link);

	str = link->prod_id[0];
	if (!str)
		goto cs_failed;
	printk("%s", str);
	str = link->prod_id[1];
	if (!str)
		goto cs_failed;
	printk(" %s", str);
	str = link->prod_id[2];
	if (!str)
		goto cs_failed;
	place = 1;
	for (i = strlen(str) - 1; i >= 0; i--) {
		switch (str[i]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			j->serial += (str[i] - 48) * place;
			break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			j->serial += (str[i] - 55) * place;
			break;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			j->serial += (str[i] - 87) * place;
			break;
		}
		place = place * 0x10;
	}
	str = link->prod_id[3];
	if (!str)
		goto cs_failed;
	printk(" version %s\n", str);
      cs_failed:
	return;
}