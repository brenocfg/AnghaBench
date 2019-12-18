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
typedef  int uint32_t ;
typedef  size_t uint ;
struct TYPE_2__ {int* sec_name; } ;
struct usm_user {size_t user_engine_len; size_t* user_engine_id; TYPE_1__ suser; } ;
struct asn_oid {size_t len; size_t* subs; } ;

/* Variables and functions */
 size_t strlen (int*) ; 

__attribute__((used)) static void
usm_append_userindex(struct asn_oid *oid, uint sub,
    const struct usm_user *uuser)
{
	uint32_t i;

	oid->len = sub + uuser->user_engine_len + strlen(uuser->suser.sec_name);
	oid->len += 2;
	oid->subs[sub] = uuser->user_engine_len;
	for (i = 1; i < uuser->user_engine_len + 1; i++)
		oid->subs[sub + i] = uuser->user_engine_id[i - 1];

	sub += uuser->user_engine_len + 1;
	oid->subs[sub] = strlen(uuser->suser.sec_name);
	for (i = 1; i <= oid->subs[sub]; i++)
		oid->subs[sub + i] = uuser->suser.sec_name[i - 1];
}