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
struct nls_table {int (* char2uni ) (char const*,int,char*) ;int (* uni2char ) (char,char*,int) ;} ;
struct hfs_name {char* name; int len; } ;
struct TYPE_2__ {struct nls_table* nls_io; struct nls_table* nls_disk; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int HFS_MAX_NAMELEN ; 
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int stub1 (char const*,int,char*) ; 
 int stub2 (char,char*,int) ; 

int hfs_mac2asc(struct super_block *sb, char *out, const struct hfs_name *in)
{
	struct nls_table *nls_disk = HFS_SB(sb)->nls_disk;
	struct nls_table *nls_io = HFS_SB(sb)->nls_io;
	const char *src;
	char *dst;
	int srclen, dstlen, size;

	src = in->name;
	srclen = in->len;
	dst = out;
	dstlen = HFS_MAX_NAMELEN;
	if (nls_io) {
		wchar_t ch;

		while (srclen > 0) {
			if (nls_disk) {
				size = nls_disk->char2uni(src, srclen, &ch);
				if (size <= 0) {
					ch = '?';
					size = 1;
				}
				src += size;
				srclen -= size;
			} else {
				ch = *src++;
				srclen--;
			}
			if (ch == '/')
				ch = ':';
			size = nls_io->uni2char(ch, dst, dstlen);
			if (size < 0) {
				if (size == -ENAMETOOLONG)
					goto out;
				*dst = '?';
				size = 1;
			}
			dst += size;
			dstlen -= size;
		}
	} else {
		char ch;

		while (--srclen >= 0)
			*dst++ = (ch = *src++) == '/' ? ':' : ch;
	}
out:
	return dst - out;
}