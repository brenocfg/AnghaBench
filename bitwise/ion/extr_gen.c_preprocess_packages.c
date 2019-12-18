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

/* Variables and functions */
 size_t buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * package_list ; 
 int /*<<< orphan*/  preprocess_package (int /*<<< orphan*/ ) ; 

void preprocess_packages(void) {
    for (size_t i = 0; i < buf_len(package_list); i++) {
        preprocess_package(package_list[i]);
    }
}