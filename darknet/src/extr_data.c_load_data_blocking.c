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
struct load_args {int dummy; } ;
typedef  struct load_args load_args ;

/* Variables and functions */
 struct load_args* calloc (int,int) ; 
 int /*<<< orphan*/  load_thread (struct load_args*) ; 

void load_data_blocking(load_args args)
{
    struct load_args *ptr = calloc(1, sizeof(struct load_args));
    *ptr = args;
    load_thread(ptr);
}