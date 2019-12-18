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
struct internal_exec {int dummy; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  N_DRELOFF (struct internal_exec) ; 
 int /*<<< orphan*/  N_SYMOFF (struct internal_exec) ; 
 int /*<<< orphan*/  N_TRELOFF (struct internal_exec) ; 
 struct internal_exec* exec_hdr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
MY_final_link_callback (bfd *abfd,
			file_ptr *ptreloff,
			file_ptr *pdreloff,
			file_ptr *psymoff)
{
  struct internal_exec *execp = exec_hdr (abfd);

  *ptreloff = N_TRELOFF (*execp);
  *pdreloff = N_DRELOFF (*execp);
  *psymoff = N_SYMOFF (*execp);
}