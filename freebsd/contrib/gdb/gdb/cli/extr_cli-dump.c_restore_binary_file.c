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
struct callback_data {long load_start; long load_end; scalar_t__ load_offset; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/ * fopen_with_cleanup (char*,int /*<<< orphan*/ ) ; 
 long fread (char*,int,long,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  safe_strerror (long) ; 
 long target_write_memory (scalar_t__,char*,long) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (long) ; 

__attribute__((used)) static void
restore_binary_file (char *filename, struct callback_data *data)
{
  FILE *file = fopen_with_cleanup (filename, FOPEN_RB);
  int status;
  char *buf;
  long len;

  /* Get the file size for reading.  */
  if (fseek (file, 0, SEEK_END) == 0)
    len = ftell (file);
  else
    perror_with_name (filename);

  if (len <= data->load_start)
    error ("Start address is greater than length of binary file %s.", 
	   filename);

  /* Chop off "len" if it exceeds the requested load_end addr. */
  if (data->load_end != 0 && data->load_end < len)
    len = data->load_end;
  /* Chop off "len" if the requested load_start addr skips some bytes. */
  if (data->load_start > 0)
    len -= data->load_start;

  printf_filtered 
    ("Restoring binary file %s into memory (0x%lx to 0x%lx)\n", 
     filename, 
     (unsigned long) data->load_start + data->load_offset, 
     (unsigned long) data->load_start + data->load_offset + len);

  /* Now set the file pos to the requested load start pos.  */
  if (fseek (file, data->load_start, SEEK_SET) != 0)
    perror_with_name (filename);

  /* Now allocate a buffer and read the file contents.  */
  buf = xmalloc (len);
  make_cleanup (xfree, buf);
  if (fread (buf, 1, len, file) != len)
    perror_with_name (filename);

  /* Now write the buffer into target memory. */
  len = target_write_memory (data->load_start + data->load_offset, buf, len);
  if (len != 0)
    warning ("restore: memory write failed (%s).", safe_strerror (len));
  return;
}