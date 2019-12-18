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
struct opncls {scalar_t__ (* pread ) (struct bfd*,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  where; int /*<<< orphan*/  stream; } ;
struct bfd {struct opncls* iostream; } ;
typedef  scalar_t__ file_ptr ;

/* Variables and functions */
 scalar_t__ stub1 (struct bfd*,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static file_ptr
opncls_bread (struct bfd *abfd, void *buf, file_ptr nbytes)
{
  struct opncls *vec = abfd->iostream;
  file_ptr nread = (vec->pread) (abfd, vec->stream, buf, nbytes, vec->where);
  if (nread < 0)
    return nread;
  vec->where += nread;
  return nread;
}