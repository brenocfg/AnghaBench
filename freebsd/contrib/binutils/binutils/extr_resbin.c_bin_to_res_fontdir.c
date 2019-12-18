#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_fontdir_item {char const* index; } ;
typedef  int rc_uint_type ;
struct TYPE_5__ {TYPE_3__* fontdir; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
struct TYPE_7__ {unsigned int length; char const* data; struct TYPE_7__* next; void* index; } ;
typedef  TYPE_3__ rc_fontdir ;
typedef  char bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_FONTDIR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static rc_res_resource *
bin_to_res_fontdir (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length)
{
  rc_uint_type c, i;
  rc_fontdir *first, **pp;
  rc_res_resource *r;

  if (length < 2)
    toosmall (_("fontdir header"));

  c = windres_get_16 (wrbfd, data, 2);

  first = NULL;
  pp = &first;

  for (i = 0; i < c; i++)
    {
      const struct bin_fontdir_item *bfi;
      rc_fontdir *fd;
      unsigned int off;

      if (length < 56)
	toosmall (_("fontdir"));

      bfi = (const struct bin_fontdir_item *) data;
      fd = (rc_fontdir *) res_alloc (sizeof *fd);
      fd->index = windres_get_16 (wrbfd, bfi->index, 2);

      /* To work out the length of the fontdir data, we must get the
         length of the device name and face name strings, even though
         we don't store them in the rc_fontdir.  The
         documentation says that these are NULL terminated char
         strings, not Unicode strings.  */

      off = 56;

      while (off < length && data[off] != '\0')
	++off;
      if (off >= length)
	toosmall (_("fontdir device name"));
      ++off;

      while (off < length && data[off] != '\0')
	++off;
      if (off >= length)
	toosmall (_("fontdir face name"));
      ++off;

      fd->length = off;
      fd->data = data;

      fd->next = NULL;
      *pp = fd;
      pp = &fd->next;

      /* The documentation does not indicate that any rounding is
         required.  */

      data += off;
      length -= off;
    }

  r = (rc_res_resource *) res_alloc (sizeof *r);
  r->type = RES_TYPE_FONTDIR;
  r->u.fontdir = first;

  return r;
}