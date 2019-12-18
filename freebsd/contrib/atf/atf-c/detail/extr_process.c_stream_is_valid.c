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
struct TYPE_3__ {scalar_t__ m_type; } ;
typedef  TYPE_1__ atf_process_stream_t ;

/* Variables and functions */
 scalar_t__ atf_process_stream_type_capture ; 
 scalar_t__ atf_process_stream_type_connect ; 
 scalar_t__ atf_process_stream_type_inherit ; 
 scalar_t__ atf_process_stream_type_redirect_fd ; 
 scalar_t__ atf_process_stream_type_redirect_path ; 

__attribute__((used)) static
bool
stream_is_valid(const atf_process_stream_t *sb)
{
    return (sb->m_type == atf_process_stream_type_capture) ||
           (sb->m_type == atf_process_stream_type_connect) ||
           (sb->m_type == atf_process_stream_type_inherit) ||
           (sb->m_type == atf_process_stream_type_redirect_fd) ||
           (sb->m_type == atf_process_stream_type_redirect_path);
}