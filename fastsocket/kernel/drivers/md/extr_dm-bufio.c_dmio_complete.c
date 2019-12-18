#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* bi_end_io ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct dm_buffer {TYPE_1__ bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmio_complete(unsigned long error, void *context)
{
	struct dm_buffer *b = context;

	b->bio.bi_end_io(&b->bio, error ? -EIO : 0);
}