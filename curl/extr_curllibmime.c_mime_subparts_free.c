#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* parent; } ;
typedef  TYPE_1__ curl_mime ;
struct TYPE_5__ {int /*<<< orphan*/ * freefunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_part_content (TYPE_3__*) ; 
 int /*<<< orphan*/  curl_mime_free (TYPE_1__*) ; 

__attribute__((used)) static void mime_subparts_free(void *ptr)
{
  curl_mime *mime = (curl_mime *) ptr;

  if(mime && mime->parent) {
    mime->parent->freefunc = NULL;  /* Be sure we won't be called again. */
    cleanup_part_content(mime->parent);  /* Avoid dangling pointer in part. */
  }
  curl_mime_free(mime);
}