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
typedef  scalar_t__ pthread_t ;
typedef  int /*<<< orphan*/  TaskHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_get_handle_by_desc ; 
 int /*<<< orphan*/  pthread_list_find_item (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline TaskHandle_t pthread_find_handle(pthread_t thread)
{
    return pthread_list_find_item(pthread_get_handle_by_desc, (void *)thread);
}