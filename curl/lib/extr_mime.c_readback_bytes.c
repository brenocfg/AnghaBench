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
struct TYPE_3__ {size_t offset; } ;
typedef  TYPE_1__ mime_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t readback_bytes(mime_state *state,
                             char *buffer, size_t bufsize,
                             const char *bytes, size_t numbytes,
                             const char *trail)
{
  size_t sz;

  if(numbytes > state->offset) {
    sz = numbytes - state->offset;
    bytes += state->offset;
  }
  else {
    size_t tsz = strlen(trail);

    sz = state->offset - numbytes;
    if(sz >= tsz)
      return 0;
    bytes = trail + sz;
    sz = tsz - sz;
  }

  if(sz > bufsize)
    sz = bufsize;

  memcpy(buffer, bytes, sz);
  state->offset += sz;
  return sz;
}