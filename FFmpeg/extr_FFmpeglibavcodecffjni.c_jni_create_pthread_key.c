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
 int /*<<< orphan*/  current_env ; 
 int /*<<< orphan*/  jni_detach_env ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jni_create_pthread_key(void)
{
    pthread_key_create(&current_env, jni_detach_env);
}