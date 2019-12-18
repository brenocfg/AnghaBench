#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_target ;
typedef  int /*<<< orphan*/  bfd_size_type ;
struct TYPE_7__ {int /*<<< orphan*/  const* xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  ISHEX (char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_bread (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ bfd_seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_phase ; 
 int /*<<< orphan*/  pass_over (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tekhex_init () ; 
 int /*<<< orphan*/  tekhex_mkobject (TYPE_1__*) ; 

__attribute__((used)) static const bfd_target *
tekhex_object_p (bfd *abfd)
{
  char b[4];

  tekhex_init ();

  if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0
      || bfd_bread (b, (bfd_size_type) 4, abfd) != 4)
    return NULL;

  if (b[0] != '%' || !ISHEX (b[1]) || !ISHEX (b[2]) || !ISHEX (b[3]))
    return NULL;

  tekhex_mkobject (abfd);

  if (!pass_over (abfd, first_phase))
    return NULL;

  return abfd->xvec;
}