#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_type; } ;
typedef  TYPE_1__ atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  POST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_process_stream_type_inherit ; 
 int /*<<< orphan*/  stream_is_valid (TYPE_1__*) ; 

atf_error_t
atf_process_stream_init_inherit(atf_process_stream_t *sb)
{
    sb->m_type = atf_process_stream_type_inherit;

    POST(stream_is_valid(sb));
    return atf_no_error();
}