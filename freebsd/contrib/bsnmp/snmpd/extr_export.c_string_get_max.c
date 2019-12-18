#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/ * octets; scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {TYPE_2__ v; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_RES_UNAVAIL ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int strlen (int /*<<< orphan*/  const*) ; 

int
string_get_max(struct snmp_value *value, const u_char *ptr, ssize_t len,
    size_t maxlen)
{

	if (ptr == NULL) {
		value->v.octetstring.len = 0;
		value->v.octetstring.octets = NULL;
		return (SNMP_ERR_NOERROR);
	}
	if (len == -1)
		len = strlen(ptr);
	if ((size_t)len > maxlen)
		len = maxlen;
	if ((value->v.octetstring.octets = malloc((size_t)len)) == NULL) {
		value->v.octetstring.len = 0;
		return (SNMP_ERR_RES_UNAVAIL);
	}
	value->v.octetstring.len = (u_long)len;
	memcpy(value->v.octetstring.octets, ptr, (size_t)len);
	return (SNMP_ERR_NOERROR);
}