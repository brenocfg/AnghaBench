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
struct TYPE_3__ {int /*<<< orphan*/  gf; int /*<<< orphan*/  isaac; } ;
typedef  TYPE_1__ qr_reader ;

/* Variables and functions */
 int /*<<< orphan*/  QR_PPOLY ; 
 int /*<<< orphan*/  isaac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_gf256_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_reader_init (qr_reader *reader)
{
    /*time_t now;
      now=time(NULL);
      isaac_init(&_reader->isaac,&now,sizeof(now));*/
    isaac_init(&reader->isaac, NULL, 0);
    rs_gf256_init(&reader->gf, QR_PPOLY);
}