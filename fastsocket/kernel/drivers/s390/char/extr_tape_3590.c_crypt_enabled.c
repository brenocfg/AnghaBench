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
struct tape_device {int dummy; } ;

/* Variables and functions */
 int TAPE390_CRYPT_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAPE_3590_CRYPT_INFO (struct tape_device*) ; 

__attribute__((used)) static int crypt_enabled(struct tape_device *device)
{
	return TAPE390_CRYPT_ON(TAPE_3590_CRYPT_INFO(device));
}