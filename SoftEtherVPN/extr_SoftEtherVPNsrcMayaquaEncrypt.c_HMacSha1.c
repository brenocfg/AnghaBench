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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  Internal_HMac (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

UINT HMacSha1(void *dst, void *key, UINT key_size, void *src, UINT src_size)
{
	return Internal_HMac(EVP_sha1(), dst, key, key_size, src, src_size);
}