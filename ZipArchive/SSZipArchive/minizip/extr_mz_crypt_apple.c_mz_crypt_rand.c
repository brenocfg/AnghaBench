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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ SecRandomCopyBytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errSecSuccess ; 
 int /*<<< orphan*/  kSecRandomDefault ; 

int32_t mz_crypt_rand(uint8_t *buf, int32_t size)
{
    if (SecRandomCopyBytes(kSecRandomDefault, size, buf) != errSecSuccess)
        return 0;
    return size;
}