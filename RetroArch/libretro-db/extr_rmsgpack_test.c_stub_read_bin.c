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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stub_state_post_print (void*) ; 
 int /*<<< orphan*/  stub_state_pre_print (void*) ; 

__attribute__((used)) static int stub_read_bin(
        void * s,
        uint32_t len,
        void * data
){
	stub_state_pre_print(data);
	printf("b'%s'", (char*)s);
	stub_state_post_print(data);
	free(s);
	return 0;
}