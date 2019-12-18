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
struct TYPE_4__ {void* body; void* header; int /*<<< orphan*/  body_len; int /*<<< orphan*/  header_len; } ;
typedef  TYPE_1__ ogg_page ;

/* Variables and functions */
 void* ogg_buffer_dup (void*) ; 

void ogg_page_dup(ogg_page *dup,ogg_page *orig){
  dup->header_len=orig->header_len;
  dup->body_len=orig->body_len;
  dup->header=ogg_buffer_dup(orig->header);
  dup->body=ogg_buffer_dup(orig->body);
}