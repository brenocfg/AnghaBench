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

/* Variables and functions */
 int HDR_GET_LEN (unsigned char*) ; 
 int HDR_GET_SEQ (unsigned char*) ; 
 size_t HDR_INDX_LEN1 ; 
 size_t HDR_INDX_SEQ ; 
 size_t HDR_INDX_SYN ; 
 size_t HDR_INDX_TYPE_LEN ; 
 int /*<<< orphan*/  HDR_IS_DATA (unsigned char*) ; 
 int HDR_LENGTH ; 
 unsigned char HDR_SET_LEN1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char HDR_SET_SEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char HDR_SET_SYN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char HDR_SET_TYPE_LEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SEQ_MODULOS ; 
 int SERIAL_TIMEOUT ; 
 int SYN ; 
 unsigned char* TRLR_GET_CKSUM (unsigned char*) ; 
 int TRLR_INDX_CSUM1 ; 
 int TRLR_INDX_CSUM2 ; 
 int TRLR_INDX_CSUM3 ; 
 int TRLR_LENGTH ; 
 unsigned char TRLR_SET_CSUM1 (int) ; 
 unsigned char TRLR_SET_CSUM2 (int) ; 
 unsigned char TRLR_SET_CSUM3 (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int mips_cksum (unsigned char*,...) ; 
 int /*<<< orphan*/  mips_desc ; 
 int /*<<< orphan*/  mips_error (char*,...) ; 
 int mips_readchar (int) ; 
 scalar_t__ mips_receive_header (unsigned char*,int*,int,int) ; 
 int mips_receive_seq ; 
 int mips_receive_trailer (unsigned char*,int*,int*,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_write (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
mips_receive_packet (char *buff, int throw_error, int timeout)
{
  int ch;
  int garbage;
  int len;
  unsigned char ack[HDR_LENGTH + TRLR_LENGTH + 1];
  int cksum;

  ch = 0;
  garbage = 0;
  while (1)
    {
      unsigned char hdr[HDR_LENGTH];
      unsigned char trlr[TRLR_LENGTH];
      int i;
      int err;

      if (mips_receive_header (hdr, &garbage, ch, timeout) != 0)
	{
	  if (throw_error)
	    mips_error ("Timed out waiting for remote packet");
	  else
	    return -1;
	}

      ch = 0;

      /* An acknowledgement is probably a duplicate; ignore it.  */
      if (!HDR_IS_DATA (hdr))
	{
	  len = HDR_GET_LEN (hdr);
	  /* Check if the length is valid for an ACK, we may aswell
	     try and read the remainder of the packet: */
	  if (len == 0)
	    {
	      /* Ignore the error condition, since we are going to
	         ignore the packet anyway. */
	      (void) mips_receive_trailer (trlr, &garbage, &ch, timeout);
	    }
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    fprintf_unfiltered (gdb_stdlog, "Ignoring unexpected ACK\n");
	  continue;
	}

      len = HDR_GET_LEN (hdr);
      for (i = 0; i < len; i++)
	{
	  int rch;

	  rch = mips_readchar (timeout);
	  if (rch == SYN)
	    {
	      ch = SYN;
	      break;
	    }
	  if (rch == SERIAL_TIMEOUT)
	    {
	      if (throw_error)
		mips_error ("Timed out waiting for remote packet");
	      else
		return -1;
	    }
	  buff[i] = rch;
	}

      if (i < len)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    fprintf_unfiltered (gdb_stdlog,
				"Got new SYN after %d chars (wanted %d)\n",
				i, len);
	  continue;
	}

      err = mips_receive_trailer (trlr, &garbage, &ch, timeout);
      if (err == -1)
	{
	  if (throw_error)
	    mips_error ("Timed out waiting for packet");
	  else
	    return -1;
	}
      if (err == -2)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    fprintf_unfiltered (gdb_stdlog, "Got SYN when wanted trailer\n");
	  continue;
	}

      /* If this is the wrong sequence number, ignore it.  */
      if (HDR_GET_SEQ (hdr) != mips_receive_seq)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    fprintf_unfiltered (gdb_stdlog,
				"Ignoring sequence number %d (want %d)\n",
				HDR_GET_SEQ (hdr), mips_receive_seq);
	  continue;
	}

      if (mips_cksum (hdr, buff, len) == TRLR_GET_CKSUM (trlr))
	break;

      if (remote_debug > 0)
	/* Don't use _filtered; we can't deal with a QUIT out of
	   target_wait, and I think this might be called from there.  */
	printf_unfiltered ("Bad checksum; data %d, trailer %d\n",
			   mips_cksum (hdr, buff, len),
			   TRLR_GET_CKSUM (trlr));

      /* The checksum failed.  Send an acknowledgement for the
         previous packet to tell the remote to resend the packet.  */
      ack[HDR_INDX_SYN] = HDR_SET_SYN (0, 0, mips_receive_seq);
      ack[HDR_INDX_TYPE_LEN] = HDR_SET_TYPE_LEN (0, 0, mips_receive_seq);
      ack[HDR_INDX_LEN1] = HDR_SET_LEN1 (0, 0, mips_receive_seq);
      ack[HDR_INDX_SEQ] = HDR_SET_SEQ (0, 0, mips_receive_seq);

      cksum = mips_cksum (ack, (unsigned char *) NULL, 0);

      ack[HDR_LENGTH + TRLR_INDX_CSUM1] = TRLR_SET_CSUM1 (cksum);
      ack[HDR_LENGTH + TRLR_INDX_CSUM2] = TRLR_SET_CSUM2 (cksum);
      ack[HDR_LENGTH + TRLR_INDX_CSUM3] = TRLR_SET_CSUM3 (cksum);

      if (remote_debug > 0)
	{
	  ack[HDR_LENGTH + TRLR_LENGTH] = '\0';
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  printf_unfiltered ("Writing ack %d \"%s\"\n", mips_receive_seq,
			     ack + 1);
	}

      if (serial_write (mips_desc, ack, HDR_LENGTH + TRLR_LENGTH) != 0)
	{
	  if (throw_error)
	    mips_error ("write to target failed: %s", safe_strerror (errno));
	  else
	    return -1;
	}
    }

  if (remote_debug > 0)
    {
      buff[len] = '\0';
      /* Don't use _filtered; we can't deal with a QUIT out of
         target_wait, and I think this might be called from there.  */
      printf_unfiltered ("Got packet \"%s\"\n", buff);
    }

  /* We got the packet.  Send an acknowledgement.  */
  mips_receive_seq = (mips_receive_seq + 1) % SEQ_MODULOS;

  ack[HDR_INDX_SYN] = HDR_SET_SYN (0, 0, mips_receive_seq);
  ack[HDR_INDX_TYPE_LEN] = HDR_SET_TYPE_LEN (0, 0, mips_receive_seq);
  ack[HDR_INDX_LEN1] = HDR_SET_LEN1 (0, 0, mips_receive_seq);
  ack[HDR_INDX_SEQ] = HDR_SET_SEQ (0, 0, mips_receive_seq);

  cksum = mips_cksum (ack, (unsigned char *) NULL, 0);

  ack[HDR_LENGTH + TRLR_INDX_CSUM1] = TRLR_SET_CSUM1 (cksum);
  ack[HDR_LENGTH + TRLR_INDX_CSUM2] = TRLR_SET_CSUM2 (cksum);
  ack[HDR_LENGTH + TRLR_INDX_CSUM3] = TRLR_SET_CSUM3 (cksum);

  if (remote_debug > 0)
    {
      ack[HDR_LENGTH + TRLR_LENGTH] = '\0';
      /* Don't use _filtered; we can't deal with a QUIT out of
         target_wait, and I think this might be called from there.  */
      printf_unfiltered ("Writing ack %d \"%s\"\n", mips_receive_seq,
			 ack + 1);
    }

  if (serial_write (mips_desc, ack, HDR_LENGTH + TRLR_LENGTH) != 0)
    {
      if (throw_error)
	mips_error ("write to target failed: %s", safe_strerror (errno));
      else
	return -1;
    }

  return len;
}