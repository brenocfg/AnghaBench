#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int dummy; } ;
struct TYPE_3__ {scalar_t__ downstream; } ;
typedef  TYPE_1__ contenc_writer ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_WRITE_ERROR ; 

__attribute__((used)) static CURLcode identity_init_writer(struct connectdata *conn,
                                     contenc_writer *writer)
{
  (void) conn;
  return writer->downstream? CURLE_OK: CURLE_WRITE_ERROR;
}