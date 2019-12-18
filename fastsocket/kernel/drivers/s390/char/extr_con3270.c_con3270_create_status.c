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
struct TYPE_3__ {int cols; int rows; int /*<<< orphan*/  ascebc; int /*<<< orphan*/  dev; } ;
struct con3270 {TYPE_2__* status; TYPE_1__ view; int /*<<< orphan*/  freemem; } ;
typedef  int /*<<< orphan*/  blueprint ;
struct TYPE_4__ {scalar_t__ string; } ;

/* Variables and functions */
#define  TAC_GREEN 134 
#define  TAT_COLOR 133 
#define  TF_LOG 132 
#define  TO_RA 131 
#define  TO_SA 130 
#define  TO_SBA 129 
#define  TO_SF 128 
 TYPE_2__* alloc_string (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  codepage_convert (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  raw3270_buffer_address (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
con3270_create_status(struct con3270 *cp)
{
	static const unsigned char blueprint[] =
		{ TO_SBA, 0, 0, TO_SF,TF_LOG,TO_SA,TAT_COLOR, TAC_GREEN,
		  'c','o','n','s','o','l','e',' ','v','i','e','w',
		  TO_RA,0,0,0,'R','u','n','n','i','n','g',TO_SF,TF_LOG };

	cp->status = alloc_string(&cp->freemem, sizeof(blueprint));
	/* Copy blueprint to status line */
	memcpy(cp->status->string, blueprint, sizeof(blueprint));
	/* Set TO_RA addresses. */
	raw3270_buffer_address(cp->view.dev, cp->status->string + 1,
			       cp->view.cols * (cp->view.rows - 1));
	raw3270_buffer_address(cp->view.dev, cp->status->string + 21,
			       cp->view.cols * cp->view.rows - 8);
	/* Convert strings to ebcdic. */
	codepage_convert(cp->view.ascebc, cp->status->string + 8, 12);
	codepage_convert(cp->view.ascebc, cp->status->string + 24, 7);
}