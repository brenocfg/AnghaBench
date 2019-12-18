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
typedef  void u8 ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 void* PTR_ALIGN (void*,scalar_t__) ; 
 scalar_t__ crypto_aead_alignmask (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 

__attribute__((used)) static inline u8 *esp_tmp_iv(struct crypto_aead *aead, void *tmp)
{
	return crypto_aead_ivsize(aead) ?
	       PTR_ALIGN((u8 *)tmp, crypto_aead_alignmask(aead) + 1) : tmp;
}