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
struct opncls {int (* close ) (struct bfd*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  stream; } ;
struct bfd {struct opncls* iostream; } ;

/* Variables and functions */
 int stub1 (struct bfd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
opncls_bclose (struct bfd *abfd)
{
  struct opncls *vec = abfd->iostream;
  /* Since the VEC's memory is bound to the bfd deleting the bfd will
     free it.  */
  int status = 0;
  if (vec->close != NULL)
    status = (vec->close) (abfd, vec->stream);
  abfd->iostream = NULL;
  return status;
}