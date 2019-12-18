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
struct nis_callback_data {int /*<<< orphan*/  ncd_map; int /*<<< orphan*/  ncd_m; int /*<<< orphan*/  (* ncd_fn ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int YP_NOMORE ; 
 int YP_TRUE ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 char* strnsave (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  yperr_string (int) ; 
 int ypprot_err (int) ; 

__attribute__((used)) static int
callback(int status, char *key, int kl, char *val, int vl, char *data)
{
  struct nis_callback_data *ncdp = (struct nis_callback_data *) data;

  if (status == YP_TRUE) {

    /* add to list of maps */
    char *kp = strnsave(key, kl);
    char *vp = strnsave(val, vl);

    (*ncdp->ncd_fn) (ncdp->ncd_m, kp, vp);

    /* we want more ... */
    return FALSE;

  } else {

    /* NOMORE means end of map - otherwise log error */
    if (status != YP_NOMORE) {
      /* check what went wrong */
      int e = ypprot_err(status);

      plog(XLOG_ERROR, "yp enumeration of %s: %s, status=%d, e=%d",
	   ncdp->ncd_map, yperr_string(e), status, e);
    }
    return TRUE;
  }
}