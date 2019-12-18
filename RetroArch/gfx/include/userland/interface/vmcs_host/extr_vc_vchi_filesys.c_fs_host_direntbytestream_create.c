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
struct dirent {int /*<<< orphan*/  d_modtime; int /*<<< orphan*/  d_attrib; int /*<<< orphan*/  d_size; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_NAME_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bytestream (void*,char*,int) ; 

__attribute__((used)) static int fs_host_direntbytestream_create(struct dirent *d, void *buffer)
{
   char *buf = (char*)buffer;

   // Write d_name (D_NAME_MAX_SIZE chars)
   memcpy(buf, &d->d_name, D_NAME_MAX_SIZE);
   buf += D_NAME_MAX_SIZE;

   // Write d_size (unsigned int)
   write_bytestream((void *)&d->d_size, buf, (int)sizeof(d->d_size));
   buf += 4;

   // Write d_attrib (int)
   write_bytestream((void *)&d->d_attrib, buf, (int)sizeof(d->d_attrib));
   buf += 4;

   // Write d_modtime (time_t)
   write_bytestream((void *)&d->d_modtime, buf, (int)sizeof(d->d_modtime));
   buf += 4;

   return (int)(buf-(char *)buffer);
}