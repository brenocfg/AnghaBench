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
struct Block_layout {int flags; struct Block_descriptor* descriptor; scalar_t__ invoke; int /*<<< orphan*/ * isa; } ;
struct Block_descriptor {void* reserved; void* size; scalar_t__ dispose; scalar_t__ copy; } ;

/* Variables and functions */
 int BLOCK_HAS_COPY_DISPOSE ; 
 int BLOCK_HAS_CTOR ; 
 int BLOCK_HAS_DESCRIPTOR ; 
 int BLOCK_IS_GC ; 
 int BLOCK_NEEDS_FREE ; 
 int BLOCK_REFCOUNT_MASK ; 
 int /*<<< orphan*/ * _NSConcreteAutoBlock ; 
 int /*<<< orphan*/ * _NSConcreteFinalizingBlock ; 
 int /*<<< orphan*/ * _NSConcreteGlobalBlock ; 
 int /*<<< orphan*/ * _NSConcreteMallocBlock ; 
 int /*<<< orphan*/ * _NSConcreteStackBlock ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

const char *_Block_dump(const void *block) {
    struct Block_layout *closure = (struct Block_layout *)block;
    static char buffer[512];
    char *cp = buffer;
    if (closure == NULL) {
        sprintf(cp, "NULL passed to _Block_dump\n");
        return buffer;
    }
    if (! (closure->flags & BLOCK_HAS_DESCRIPTOR)) {
        printf("Block compiled by obsolete compiler, please recompile source for this Block\n");
        exit(1);
    }
    cp += sprintf(cp, "^%p (new layout) =\n", (void *)closure);
    if (closure->isa == NULL) {
        cp += sprintf(cp, "isa: NULL\n");
    }
    else if (closure->isa == _NSConcreteStackBlock) {
        cp += sprintf(cp, "isa: stack Block\n");
    }
    else if (closure->isa == _NSConcreteMallocBlock) {
        cp += sprintf(cp, "isa: malloc heap Block\n");
    }
    else if (closure->isa == _NSConcreteAutoBlock) {
        cp += sprintf(cp, "isa: GC heap Block\n");
    }
    else if (closure->isa == _NSConcreteGlobalBlock) {
        cp += sprintf(cp, "isa: global Block\n");
    }
    else if (closure->isa == _NSConcreteFinalizingBlock) {
        cp += sprintf(cp, "isa: finalizing Block\n");
    }
    else {
        cp += sprintf(cp, "isa?: %p\n", (void *)closure->isa);
    }
    cp += sprintf(cp, "flags:");
    if (closure->flags & BLOCK_HAS_DESCRIPTOR) {
        cp += sprintf(cp, " HASDESCRIPTOR");
    }
    if (closure->flags & BLOCK_NEEDS_FREE) {
        cp += sprintf(cp, " FREEME");
    }
    if (closure->flags & BLOCK_IS_GC) {
        cp += sprintf(cp, " ISGC");
    }
    if (closure->flags & BLOCK_HAS_COPY_DISPOSE) {
        cp += sprintf(cp, " HASHELP");
    }
    if (closure->flags & BLOCK_HAS_CTOR) {
        cp += sprintf(cp, " HASCTOR");
    }
    cp += sprintf(cp, "\nrefcount: %u\n", closure->flags & BLOCK_REFCOUNT_MASK);
    cp += sprintf(cp, "invoke: %p\n", (void *)(uintptr_t)closure->invoke);
    {
        struct Block_descriptor *dp = closure->descriptor;
        cp += sprintf(cp, "descriptor: %p\n", (void *)dp);
        cp += sprintf(cp, "descriptor->reserved: %lu\n", dp->reserved);
        cp += sprintf(cp, "descriptor->size: %lu\n", dp->size);

        if (closure->flags & BLOCK_HAS_COPY_DISPOSE) {
            cp += sprintf(cp, "descriptor->copy helper: %p\n", (void *)(uintptr_t)dp->copy);
            cp += sprintf(cp, "descriptor->dispose helper: %p\n", (void *)(uintptr_t)dp->dispose);
        }
    }
    return buffer;
}