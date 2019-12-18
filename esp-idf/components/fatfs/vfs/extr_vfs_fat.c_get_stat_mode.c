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
typedef  int mode_t ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 

__attribute__((used)) static inline mode_t get_stat_mode(bool is_dir)
{
    return S_IRWXU | S_IRWXG | S_IRWXO |
            ((is_dir) ? S_IFDIR : S_IFREG);
}