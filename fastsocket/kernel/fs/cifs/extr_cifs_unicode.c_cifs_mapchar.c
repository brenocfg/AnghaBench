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
struct nls_table {int (* uni2char ) (int const,char*,int /*<<< orphan*/ ) ;} ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  NLS_MAX_CHARSET_SIZE ; 
#define  UNI_ASTERISK 133 
#define  UNI_COLON 132 
#define  UNI_GRTRTHAN 131 
#define  UNI_LESSTHAN 130 
#define  UNI_PIPE 129 
#define  UNI_QUESTION 128 
 int stub1 (int const,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_mapchar(char *target, const __u16 src_char, const struct nls_table *cp,
	     bool mapchar)
{
	int len = 1;

	if (!mapchar)
		goto cp_convert;

	/*
	 * BB: Cannot handle remapping UNI_SLASH until all the calls to
	 *     build_path_from_dentry are modified, as they use slash as
	 *     separator.
	 */
	switch (src_char) {
	case UNI_COLON:
		*target = ':';
		break;
	case UNI_ASTERISK:
		*target = '*';
		break;
	case UNI_QUESTION:
		*target = '?';
		break;
	case UNI_PIPE:
		*target = '|';
		break;
	case UNI_GRTRTHAN:
		*target = '>';
		break;
	case UNI_LESSTHAN:
		*target = '<';
		break;
	default:
		goto cp_convert;
	}

out:
	return len;

cp_convert:
	len = cp->uni2char(src_char, target, NLS_MAX_CHARSET_SIZE);
	if (len <= 0) {
		*target = '?';
		len = 1;
	}
	goto out;
}