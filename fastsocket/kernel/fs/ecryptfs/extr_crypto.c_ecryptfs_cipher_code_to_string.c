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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ cipher_code; int /*<<< orphan*/  cipher_str; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 TYPE_1__* ecryptfs_cipher_code_str_map ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int ecryptfs_cipher_code_to_string(char *str, u8 cipher_code)
{
	int rc = 0;
	int i;

	str[0] = '\0';
	for (i = 0; i < ARRAY_SIZE(ecryptfs_cipher_code_str_map); i++)
		if (cipher_code == ecryptfs_cipher_code_str_map[i].cipher_code)
			strcpy(str, ecryptfs_cipher_code_str_map[i].cipher_str);
	if (str[0] == '\0') {
		ecryptfs_printk(KERN_WARNING, "Cipher code not recognized: "
				"[%d]\n", cipher_code);
		rc = -EINVAL;
	}
	return rc;
}