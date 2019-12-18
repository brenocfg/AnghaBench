#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  char u_char ;
struct TYPE_5__ {int len; int /*<<< orphan*/  octets; } ;
struct TYPE_6__ {TYPE_2__ octetstring; } ;
struct snmp_value {TYPE_3__ v; } ;
struct snmp_context {TYPE_1__* scratch; } ;
typedef  int ssize_t ;
struct TYPE_4__ {char* ptr1; } ;

/* Variables and functions */
 int SNMP_ERR_BADVALUE ; 
 int SNMP_ERR_RES_UNAVAIL ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

int
string_save(struct snmp_value *value, struct snmp_context *ctx,
    ssize_t req_size, u_char **valp)
{
	if (req_size != -1 && value->v.octetstring.len != (u_long)req_size)
		return (SNMP_ERR_BADVALUE);

	ctx->scratch->ptr1 = *valp;

	if ((*valp = malloc(value->v.octetstring.len + 1)) == NULL) {
		*valp = ctx->scratch->ptr1;
		return (SNMP_ERR_RES_UNAVAIL);
	}

	memcpy(*valp, value->v.octetstring.octets, value->v.octetstring.len);
	(*valp)[value->v.octetstring.len] = '\0';

	return (0);
}