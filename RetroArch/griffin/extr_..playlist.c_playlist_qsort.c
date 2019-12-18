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
struct playlist_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 scalar_t__ playlist_qsort_func ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int (*) (void const*,void const*)) ; 

void playlist_qsort(playlist_t *playlist)
{
   qsort(playlist->entries, playlist->size,
         sizeof(struct playlist_entry),
         (int (*)(const void *, const void *))playlist_qsort_func);
}