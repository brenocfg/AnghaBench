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
struct sockaddr_dn {unsigned char sdn_objnum; void* sdn_objnamel; int /*<<< orphan*/  sdn_objname; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_MAXOBJL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dn_username2sockaddr(unsigned char *data, int len, struct sockaddr_dn *sdn, unsigned char *fmt)
{
	unsigned char type;
	int size = len;
	int namel = 12;

	sdn->sdn_objnum = 0;
	sdn->sdn_objnamel = cpu_to_le16(0);
	memset(sdn->sdn_objname, 0, DN_MAXOBJL);

	if (len < 2)
		return -1;

	len -= 2;
	*fmt = *data++;
	type = *data++;

	switch(*fmt) {
		case 0:
			sdn->sdn_objnum = type;
			return 2;
		case 1:
			namel = 16;
			break;
		case 2:
			len  -= 4;
			data += 4;
			break;
		case 4:
			len  -= 8;
			data += 8;
			break;
		default:
			return -1;
	}

	len -= 1;

	if (len < 0)
		return -1;

	sdn->sdn_objnamel = cpu_to_le16(*data++);
	len -= le16_to_cpu(sdn->sdn_objnamel);

	if ((len < 0) || (le16_to_cpu(sdn->sdn_objnamel) > namel))
		return -1;

	memcpy(sdn->sdn_objname, data, le16_to_cpu(sdn->sdn_objnamel));

	return size - len;
}