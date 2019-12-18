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
struct data {int dummy; } ;

/* Variables and functions */
 struct data data_append_byte (struct data,char) ; 
 struct data data_append_data (struct data,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void bin_emit_string(void *e, char *str, int len)
{
	struct data *dtbuf = e;

	if (len == 0)
		len = strlen(str);

	*dtbuf = data_append_data(*dtbuf, str, len);
	*dtbuf = data_append_byte(*dtbuf, '\0');
}