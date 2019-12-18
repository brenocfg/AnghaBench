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
typedef  int /*<<< orphan*/  buff ;
struct TYPE_3__ {int length; char const* buff; } ;
typedef  TYPE_1__ BufferInfo ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  bin2hex (char*,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  my_md5_buffer (char*,int,unsigned char*) ; 
 scalar_t__ sprintf (char*,char*,int const) ; 
 int strlen (char const*) ; 

int fdfs_http_gen_token(const BufferInfo *secret_key, const char *file_id, \
		const int timestamp, char *token)
{
	char buff[256 + 64];
	unsigned char digit[16];
	int id_len;
	int total_len;

	id_len = strlen(file_id);
	if (id_len + secret_key->length + 12 > sizeof(buff))
	{
		return ENOSPC;
	}

	memcpy(buff, file_id, id_len);
	total_len = id_len;
	memcpy(buff + total_len, secret_key->buff, secret_key->length);
	total_len += secret_key->length;
	total_len += sprintf(buff + total_len, "%d", timestamp);

	my_md5_buffer(buff, total_len, digit);
	bin2hex((char *)digit, 16, token);
	return 0;
}