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
struct connectdata {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  FTP_RETR_PREQUOTE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ftp_state_quote (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_retr_prequote(struct connectdata *conn)
{
  /* We've sent the TYPE, now we must send the list of prequote strings */
  return ftp_state_quote(conn, TRUE, FTP_RETR_PREQUOTE);
}