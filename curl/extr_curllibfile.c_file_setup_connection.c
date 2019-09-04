#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {TYPE_2__* data; } ;
struct FILEPROTO {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  calloc (int,int) ; 

__attribute__((used)) static CURLcode file_setup_connection(struct connectdata *conn)
{
  /* allocate the FILE specific struct */
  conn->data->req.protop = calloc(1, sizeof(struct FILEPROTO));
  if(!conn->data->req.protop)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}