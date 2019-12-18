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
typedef  int ttreq_t ;
typedef  int register_value_t ;
typedef  int /*<<< orphan*/  register_value ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int TTRACE_ARG_TYPE ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
#define  PT_ATTACH 144 
#define  PT_CONTINUE 143 
#define  PT_DETACH 142 
#define  PT_GET_PROCESS_PATHNAME 141 
#define  PT_KILL 140 
#define  PT_RDDATA 139 
#define  PT_RDTEXT 138 
#define  PT_READ_D 137 
#define  PT_READ_I 136 
#define  PT_RUREGS 135 
#define  PT_SETTRC 134 
#define  PT_STEP 133 
#define  PT_WRDATA 132 
#define  PT_WRITE_D 131 
#define  PT_WRITE_I 130 
#define  PT_WRTEXT 129 
#define  PT_WUREGS 128 
 int TT_LWP_SINGLE ; 
 int TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_ATTACH ; 
 int TT_PROC_CONTINUE ; 
 int TT_PROC_DETACH ; 
 int TT_PROC_EXIT ; 
 int TT_PROC_GET_PATHNAME ; 
 int TT_PROC_RDDATA ; 
 int TT_PROC_RDTEXT ; 
 int TT_PROC_WRDATA ; 
 int TT_PROC_WRTEXT ; 
 int /*<<< orphan*/  TT_VERSION ; 
 int call_real_ttrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int call_ttrace (int,int,int,int,int) ; 
 int /*<<< orphan*/  map_from_gdb_tid (int) ; 
 int parent_attach_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_from_register_save_state (int,int,int*,int) ; 
 int write_to_register_save_state (int,int,int*,int) ; 

int
call_ptrace (int pt_request, int gdb_tid, PTRACE_ARG3_TYPE addr, int data)
{
  ttreq_t tt_request;
  TTRACE_ARG_TYPE tt_addr = (TTRACE_ARG_TYPE) addr;
  TTRACE_ARG_TYPE tt_data = (TTRACE_ARG_TYPE) data;
  TTRACE_ARG_TYPE tt_addr2 = TT_NIL;
  int tt_status;
  register_value_t register_value;
  int read_buf;

  /* Perform the necessary argument translation.  Note that some
     cases are funky enough in the ttrace realm that we handle them
     very specially.
   */
  switch (pt_request)
    {
      /* The following cases cannot conveniently be handled conveniently
         by merely adjusting the ptrace arguments and feeding into the
         generic call to ttrace at the bottom of this function.

         Note that because all branches of this switch end in "return",
         there's no need for any "break" statements.
       */
    case PT_SETTRC:
      return parent_attach_all (0, 0, 0);

    case PT_RUREGS:
      tt_status = read_from_register_save_state (gdb_tid,
						 tt_addr,
						 &register_value,
						 sizeof (register_value));
      if (tt_status < 0)
	return tt_status;
      return register_value;

    case PT_WUREGS:
      register_value = (int) tt_data;
      tt_status = write_to_register_save_state (gdb_tid,
						tt_addr,
						&register_value,
						sizeof (register_value));
      return tt_status;
      break;

    case PT_READ_I:
      tt_status = call_ttrace (TT_PROC_RDTEXT,	/* Implicit 4-byte xfer becomes block-xfer. */
			       gdb_tid,
			       tt_addr,
			       (TTRACE_ARG_TYPE) 4,
			       (TTRACE_ARG_TYPE) & read_buf);
      if (tt_status < 0)
	return tt_status;
      return read_buf;

    case PT_READ_D:
      tt_status = call_ttrace (TT_PROC_RDDATA,	/* Implicit 4-byte xfer becomes block-xfer. */
			       gdb_tid,
			       tt_addr,
			       (TTRACE_ARG_TYPE) 4,
			       (TTRACE_ARG_TYPE) & read_buf);
      if (tt_status < 0)
	return tt_status;
      return read_buf;

    case PT_ATTACH:
      tt_status = call_real_ttrace (TT_PROC_ATTACH,
				    map_from_gdb_tid (gdb_tid),
				    (lwpid_t) TT_NIL,
				    tt_addr,
				    (TTRACE_ARG_TYPE) TT_VERSION,
				    tt_addr2);
      if (tt_status < 0)
	return tt_status;
      return tt_status;

      /* The following cases are handled by merely adjusting the ptrace
         arguments and feeding into the generic call to ttrace.
       */
    case PT_DETACH:
      tt_request = TT_PROC_DETACH;
      break;

    case PT_WRITE_I:
      tt_request = TT_PROC_WRTEXT;	/* Translates 4-byte xfer to block-xfer. */
      tt_data = 4;		/* This many bytes. */
      tt_addr2 = (TTRACE_ARG_TYPE) & data;	/* Address of xfer source. */
      break;

    case PT_WRITE_D:
      tt_request = TT_PROC_WRDATA;	/* Translates 4-byte xfer to block-xfer. */
      tt_data = 4;		/* This many bytes. */
      tt_addr2 = (TTRACE_ARG_TYPE) & data;	/* Address of xfer source. */
      break;

    case PT_RDTEXT:
      tt_request = TT_PROC_RDTEXT;
      break;

    case PT_RDDATA:
      tt_request = TT_PROC_RDDATA;
      break;

    case PT_WRTEXT:
      tt_request = TT_PROC_WRTEXT;
      break;

    case PT_WRDATA:
      tt_request = TT_PROC_WRDATA;
      break;

    case PT_CONTINUE:
      tt_request = TT_PROC_CONTINUE;
      break;

    case PT_STEP:
      tt_request = TT_LWP_SINGLE;	/* Should not be making this request? */
      break;

    case PT_KILL:
      tt_request = TT_PROC_EXIT;
      break;

    case PT_GET_PROCESS_PATHNAME:
      tt_request = TT_PROC_GET_PATHNAME;
      break;

    default:
      tt_request = pt_request;	/* Let ttrace be the one to complain. */
      break;
    }

  return call_ttrace (tt_request,
		      gdb_tid,
		      tt_addr,
		      tt_data,
		      tt_addr2);
}