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
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 void* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_BackDown ; 
 int /*<<< orphan*/  IN_BackUp ; 
 int /*<<< orphan*/  IN_Button0Down ; 
 int /*<<< orphan*/  IN_Button0Up ; 
 int /*<<< orphan*/  IN_Button10Down ; 
 int /*<<< orphan*/  IN_Button10Up ; 
 int /*<<< orphan*/  IN_Button11Down ; 
 int /*<<< orphan*/  IN_Button11Up ; 
 int /*<<< orphan*/  IN_Button12Down ; 
 int /*<<< orphan*/  IN_Button12Up ; 
 int /*<<< orphan*/  IN_Button13Down ; 
 int /*<<< orphan*/  IN_Button13Up ; 
 int /*<<< orphan*/  IN_Button14Down ; 
 int /*<<< orphan*/  IN_Button14Up ; 
 int /*<<< orphan*/  IN_Button1Down ; 
 int /*<<< orphan*/  IN_Button1Up ; 
 int /*<<< orphan*/  IN_Button2Down ; 
 int /*<<< orphan*/  IN_Button2Up ; 
 int /*<<< orphan*/  IN_Button3Down ; 
 int /*<<< orphan*/  IN_Button3Up ; 
 int /*<<< orphan*/  IN_Button4Down ; 
 int /*<<< orphan*/  IN_Button4Up ; 
 int /*<<< orphan*/  IN_Button5Down ; 
 int /*<<< orphan*/  IN_Button5Up ; 
 int /*<<< orphan*/  IN_Button6Down ; 
 int /*<<< orphan*/  IN_Button6Up ; 
 int /*<<< orphan*/  IN_Button7Down ; 
 int /*<<< orphan*/  IN_Button7Up ; 
 int /*<<< orphan*/  IN_Button8Down ; 
 int /*<<< orphan*/  IN_Button8Up ; 
 int /*<<< orphan*/  IN_Button9Down ; 
 int /*<<< orphan*/  IN_Button9Up ; 
 int /*<<< orphan*/  IN_CenterView ; 
 int /*<<< orphan*/  IN_DownDown ; 
 int /*<<< orphan*/  IN_DownUp ; 
 int /*<<< orphan*/  IN_ForwardDown ; 
 int /*<<< orphan*/  IN_ForwardUp ; 
 int /*<<< orphan*/  IN_LeftDown ; 
 int /*<<< orphan*/  IN_LeftUp ; 
 int /*<<< orphan*/  IN_LookdownDown ; 
 int /*<<< orphan*/  IN_LookdownUp ; 
 int /*<<< orphan*/  IN_LookupDown ; 
 int /*<<< orphan*/  IN_LookupUp ; 
 int /*<<< orphan*/  IN_MLookDown ; 
 int /*<<< orphan*/  IN_MLookUp ; 
 int /*<<< orphan*/  IN_MoveleftDown ; 
 int /*<<< orphan*/  IN_MoveleftUp ; 
 int /*<<< orphan*/  IN_MoverightDown ; 
 int /*<<< orphan*/  IN_MoverightUp ; 
 int /*<<< orphan*/  IN_RightDown ; 
 int /*<<< orphan*/  IN_RightUp ; 
 int /*<<< orphan*/  IN_SpeedDown ; 
 int /*<<< orphan*/  IN_SpeedUp ; 
 int /*<<< orphan*/  IN_StrafeDown ; 
 int /*<<< orphan*/  IN_StrafeUp ; 
 int /*<<< orphan*/  IN_UpDown ; 
 int /*<<< orphan*/  IN_UpUp ; 
 void* cl_debugMove ; 
 void* cl_nodelta ; 

void CL_InitInput( void ) {
	Cmd_AddCommand ("centerview",IN_CenterView);

	Cmd_AddCommand ("+moveup",IN_UpDown);
	Cmd_AddCommand ("-moveup",IN_UpUp);
	Cmd_AddCommand ("+movedown",IN_DownDown);
	Cmd_AddCommand ("-movedown",IN_DownUp);
	Cmd_AddCommand ("+left",IN_LeftDown);
	Cmd_AddCommand ("-left",IN_LeftUp);
	Cmd_AddCommand ("+right",IN_RightDown);
	Cmd_AddCommand ("-right",IN_RightUp);
	Cmd_AddCommand ("+forward",IN_ForwardDown);
	Cmd_AddCommand ("-forward",IN_ForwardUp);
	Cmd_AddCommand ("+back",IN_BackDown);
	Cmd_AddCommand ("-back",IN_BackUp);
	Cmd_AddCommand ("+lookup", IN_LookupDown);
	Cmd_AddCommand ("-lookup", IN_LookupUp);
	Cmd_AddCommand ("+lookdown", IN_LookdownDown);
	Cmd_AddCommand ("-lookdown", IN_LookdownUp);
	Cmd_AddCommand ("+strafe", IN_StrafeDown);
	Cmd_AddCommand ("-strafe", IN_StrafeUp);
	Cmd_AddCommand ("+moveleft", IN_MoveleftDown);
	Cmd_AddCommand ("-moveleft", IN_MoveleftUp);
	Cmd_AddCommand ("+moveright", IN_MoverightDown);
	Cmd_AddCommand ("-moveright", IN_MoverightUp);
	Cmd_AddCommand ("+speed", IN_SpeedDown);
	Cmd_AddCommand ("-speed", IN_SpeedUp);
	Cmd_AddCommand ("+attack", IN_Button0Down);
	Cmd_AddCommand ("-attack", IN_Button0Up);
	Cmd_AddCommand ("+button0", IN_Button0Down);
	Cmd_AddCommand ("-button0", IN_Button0Up);
	Cmd_AddCommand ("+button1", IN_Button1Down);
	Cmd_AddCommand ("-button1", IN_Button1Up);
	Cmd_AddCommand ("+button2", IN_Button2Down);
	Cmd_AddCommand ("-button2", IN_Button2Up);
	Cmd_AddCommand ("+button3", IN_Button3Down);
	Cmd_AddCommand ("-button3", IN_Button3Up);
	Cmd_AddCommand ("+button4", IN_Button4Down);
	Cmd_AddCommand ("-button4", IN_Button4Up);
	Cmd_AddCommand ("+button5", IN_Button5Down);
	Cmd_AddCommand ("-button5", IN_Button5Up);
	Cmd_AddCommand ("+button6", IN_Button6Down);
	Cmd_AddCommand ("-button6", IN_Button6Up);
	Cmd_AddCommand ("+button7", IN_Button7Down);
	Cmd_AddCommand ("-button7", IN_Button7Up);
	Cmd_AddCommand ("+button8", IN_Button8Down);
	Cmd_AddCommand ("-button8", IN_Button8Up);
	Cmd_AddCommand ("+button9", IN_Button9Down);
	Cmd_AddCommand ("-button9", IN_Button9Up);
	Cmd_AddCommand ("+button10", IN_Button10Down);
	Cmd_AddCommand ("-button10", IN_Button10Up);
	Cmd_AddCommand ("+button11", IN_Button11Down);
	Cmd_AddCommand ("-button11", IN_Button11Up);
	Cmd_AddCommand ("+button12", IN_Button12Down);
	Cmd_AddCommand ("-button12", IN_Button12Up);
	Cmd_AddCommand ("+button13", IN_Button13Down);
	Cmd_AddCommand ("-button13", IN_Button13Up);
	Cmd_AddCommand ("+button14", IN_Button14Down);
	Cmd_AddCommand ("-button14", IN_Button14Up);
	Cmd_AddCommand ("+mlook", IN_MLookDown);
	Cmd_AddCommand ("-mlook", IN_MLookUp);

	cl_nodelta = Cvar_Get ("cl_nodelta", "0", 0);
	cl_debugMove = Cvar_Get ("cl_debugMove", "0", 0);
}