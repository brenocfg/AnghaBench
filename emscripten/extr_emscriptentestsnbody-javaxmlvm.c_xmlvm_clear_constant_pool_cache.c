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
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_BZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stringConstants ; 
 int xmlvm_constant_pool_size ; 

void xmlvm_clear_constant_pool_cache()
{
    XMLVM_BZERO(stringConstants, xmlvm_constant_pool_size * sizeof(JAVA_OBJECT));
}