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
typedef  char wchar_t ;
struct super_block {int dummy; } ;
struct qstr {char* name; int len; } ;
struct nls_table {int (* char2uni ) (char const*,int,char*) ;int (* uni2char ) (char,char*,int) ;} ;
struct hfs_name {char* name; int len; } ;
struct TYPE_2__ {struct nls_table* nls_io; struct nls_table* nls_disk; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int HFS_NAMELEN ; 
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int stub1 (char const*,int,char*) ; 
 int stub2 (char,char*,int) ; 

void hfs_asc2mac(struct super_block *sb, struct hfs_name *out, struct qstr *in)
{
	struct nls_table *nls_disk = HFS_SB(sb)->nls_disk;
	struct nls_table *nls_io = HFS_SB(sb)->nls_io;
	const char *src;
	char *dst;
	int srclen, dstlen, size;

	src = in->name;
	srclen = in->len;
	dst = out->name;
	dstlen = HFS_NAMELEN;
	if (nls_io) {
		wchar_t ch;

		while (srclen > 0) {
			size = nls_io->char2uni(src, srclen, &ch);
			if (size < 0) {
				ch = '?';
				size = 1;
			}
			src += size;
			srclen -= size;
			if (ch == ':')
				ch = '/';
			if (nls_disk) {
				size = nls_disk->uni2char(ch, dst, dstlen);
				if (size < 0) {
					if (size == -ENAMETOOLONG)
						goto out;
					*dst = '?';
					size = 1;
				}
				dst += size;
				dstlen -= size;
			} else {
				*dst++ = ch > 0xff ? '?' : ch;
				dstlen--;
			}
		}
	} else {
		char ch;

		if (dstlen > srclen)
			dstlen = srclen;
		while (--dstlen >= 0)
			*dst++ = (ch = *src++) == ':' ? '/' : ch;
	}
out:
	out->len = dst - (char *)out->name;
	dstlen = HFS_NAMELEN - out->len;
	while (--dstlen >= 0)
		*dst++ = 0;
}