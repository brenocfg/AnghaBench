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
struct TYPE_4__ {int /*<<< orphan*/  body; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ ogg_page ;

/* Variables and functions */
 int OGG_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_buffer_release (int /*<<< orphan*/ ) ; 

int ogg_page_release(ogg_page *og) {
  if(og){
    ogg_buffer_release(og->header);
    ogg_buffer_release(og->body);
    memset(og, 0, sizeof(*og));
  }
  return OGG_SUCCESS;
}