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
 int /*<<< orphan*/  tmpfiles ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delete_temp_files() {
    for (int i = 0; i < vec_len(tmpfiles); i++)
        unlink(vec_get(tmpfiles, i));
}