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

/* Variables and functions */
 int FALSE ; 
 scalar_t__ LASTLINE (char*) ; 
 int TRUE ; 
 int curlx_sltosi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool ftp_endofresp(struct connectdata *conn, char *line, size_t len,
                          int *code)
{
  (void)conn;

  if((len > 3) && LASTLINE(line)) {
    *code = curlx_sltosi(strtol(line, NULL, 10));
    return TRUE;
  }

  return FALSE;
}