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
struct sipkey {void** k; } ;

/* Variables and functions */
 void* SIP_U8TO64_LE (unsigned char const*) ; 

__attribute__((used)) static struct sipkey *sip_tokey(struct sipkey *key, const void *src) {
	key->k[0] = SIP_U8TO64_LE((const unsigned char *)src);
	key->k[1] = SIP_U8TO64_LE((const unsigned char *)src + 8);
	return key;
}