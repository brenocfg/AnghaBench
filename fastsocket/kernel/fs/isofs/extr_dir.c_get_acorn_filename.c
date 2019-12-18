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
struct iso_directory_record {int* name_len; int* flags; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int isofs_name_translate (struct iso_directory_record*,char*,struct inode*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 

int get_acorn_filename(struct iso_directory_record *de,
			    char *retname, struct inode *inode)
{
	int std;
	unsigned char *chr;
	int retnamlen = isofs_name_translate(de, retname, inode);

	if (retnamlen == 0)
		return 0;
	std = sizeof(struct iso_directory_record) + de->name_len[0];
	if (std & 1)
		std++;
	if ((*((unsigned char *) de) - std) != 32)
		return retnamlen;
	chr = ((unsigned char *) de) + std;
	if (strncmp(chr, "ARCHIMEDES", 10))
		return retnamlen;
	if ((*retname == '_') && ((chr[19] & 1) == 1))
		*retname = '!';
	if (((de->flags[0] & 2) == 0) && (chr[13] == 0xff)
		&& ((chr[12] & 0xf0) == 0xf0)) {
		retname[retnamlen] = ',';
		sprintf(retname+retnamlen+1, "%3.3x",
			((chr[12] & 0xf) << 8) | chr[11]);
		retnamlen += 4;
	}
	return retnamlen;
}