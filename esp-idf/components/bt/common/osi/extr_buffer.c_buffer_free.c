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
struct TYPE_4__ {scalar_t__ refcount; struct TYPE_4__* root; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 

void buffer_free(buffer_t *buffer)
{
    if (!buffer) {
        return;
    }

    if (buffer->root != buffer) {
        // We're a leaf node. Delete the root node if we're the last referent.
        if (--buffer->root->refcount == 0) {
            osi_free(buffer->root);
        }
        osi_free(buffer);
    } else if (--buffer->refcount == 0) {
        // We're a root node. Roots are only deleted when their refcount goes to 0.
        osi_free(buffer);
    }
}