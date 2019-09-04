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
struct TYPE_4__ {size_t size_used; char* buffer; int size_max; } ;
typedef  TYPE_1__ Curl_send_buffer ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 char* Curl_saferealloc (char*,size_t) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

CURLcode Curl_add_buffer(Curl_send_buffer **inp, const void *inptr,
                         size_t size)
{
  char *new_rb;
  Curl_send_buffer *in = *inp;

  if(~size < in->size_used) {
    /* If resulting used size of send buffer would wrap size_t, cleanup
       the whole buffer and return error. Otherwise the required buffer
       size will fit into a single allocatable memory chunk */
    Curl_safefree(in->buffer);
    free(in);
    *inp = NULL;
    return CURLE_OUT_OF_MEMORY;
  }

  if(!in->buffer ||
     ((in->size_used + size) > (in->size_max - 1))) {
    /* If current buffer size isn't enough to hold the result, use a
       buffer size that doubles the required size. If this new size
       would wrap size_t, then just use the largest possible one */
    size_t new_size;

    if((size > (size_t)-1 / 2) || (in->size_used > (size_t)-1 / 2) ||
       (~(size * 2) < (in->size_used * 2)))
      new_size = (size_t)-1;
    else
      new_size = (in->size_used + size) * 2;

    if(in->buffer)
      /* we have a buffer, enlarge the existing one */
      new_rb = Curl_saferealloc(in->buffer, new_size);
    else
      /* create a new buffer */
      new_rb = malloc(new_size);

    if(!new_rb) {
      /* If we failed, we cleanup the whole buffer and return error */
      free(in);
      *inp = NULL;
      return CURLE_OUT_OF_MEMORY;
    }

    in->buffer = new_rb;
    in->size_max = new_size;
  }
  memcpy(&in->buffer[in->size_used], inptr, size);

  in->size_used += size;

  return CURLE_OK;
}