#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_9__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_10__ {int flags; scalar_t__ lma; struct TYPE_10__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_11__ {char* to_shortname; } ;

/* Variables and functions */
 int SEC_LOAD ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_section_contents (TYPE_1__*,TYPE_2__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* bfd_get_section_name (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ bfd_get_section_size (TYPE_2__*) ; 
 unsigned long crc32 (unsigned char*,scalar_t__,int) ; 
 TYPE_3__ current_target ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 unsigned long fromhex (char) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 char* paddr (scalar_t__) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,long) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
compare_sections_command (char *args, int from_tty)
{
  struct remote_state *rs = get_remote_state ();
  asection *s;
  unsigned long host_crc, target_crc;
  extern bfd *exec_bfd;
  struct cleanup *old_chain;
  char *tmp;
  char *sectdata;
  const char *sectname;
  char *buf = alloca (rs->remote_packet_size);
  bfd_size_type size;
  bfd_vma lma;
  int matched = 0;
  int mismatched = 0;

  if (!exec_bfd)
    error ("command cannot be used without an exec file");
  if (!current_target.to_shortname ||
      strcmp (current_target.to_shortname, "remote") != 0)
    error ("command can only be used with remote target");

  for (s = exec_bfd->sections; s; s = s->next)
    {
      if (!(s->flags & SEC_LOAD))
	continue;		/* skip non-loadable section */

      size = bfd_get_section_size (s);
      if (size == 0)
	continue;		/* skip zero-length section */

      sectname = bfd_get_section_name (exec_bfd, s);
      if (args && strcmp (args, sectname) != 0)
	continue;		/* not the section selected by user */

      matched = 1;		/* do this section */
      lma = s->lma;
      /* FIXME: assumes lma can fit into long */
      sprintf (buf, "qCRC:%lx,%lx", (long) lma, (long) size);
      putpkt (buf);

      /* be clever; compute the host_crc before waiting for target reply */
      sectdata = xmalloc (size);
      old_chain = make_cleanup (xfree, sectdata);
      bfd_get_section_contents (exec_bfd, s, sectdata, 0, size);
      host_crc = crc32 ((unsigned char *) sectdata, size, 0xffffffff);

      getpkt (buf, (rs->remote_packet_size), 0);
      if (buf[0] == 'E')
	error ("target memory fault, section %s, range 0x%s -- 0x%s",
	       sectname, paddr (lma), paddr (lma + size));
      if (buf[0] != 'C')
	error ("remote target does not support this operation");

      for (target_crc = 0, tmp = &buf[1]; *tmp; tmp++)
	target_crc = target_crc * 16 + fromhex (*tmp);

      printf_filtered ("Section %s, range 0x%s -- 0x%s: ",
		       sectname, paddr (lma), paddr (lma + size));
      if (host_crc == target_crc)
	printf_filtered ("matched.\n");
      else
	{
	  printf_filtered ("MIS-MATCHED!\n");
	  mismatched++;
	}

      do_cleanups (old_chain);
    }
  if (mismatched > 0)
    warning ("One or more sections of the remote executable does not match\n\
the loaded file\n");
  if (args && !matched)
    printf_filtered ("No loaded section named '%s'.\n", args);
}