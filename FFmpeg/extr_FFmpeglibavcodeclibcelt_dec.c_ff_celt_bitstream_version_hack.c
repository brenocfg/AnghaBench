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
struct TYPE_3__ {int version_id; } ;
typedef  int /*<<< orphan*/  CELTMode ;
typedef  TYPE_1__ CELTHeader ;

/* Variables and functions */
 int /*<<< orphan*/  celt_header_init (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int ff_celt_bitstream_version_hack(CELTMode *mode)
{
    CELTHeader header = { .version_id = 0 };
    celt_header_init(&header, mode, 960, 2);
    return header.version_id;
}