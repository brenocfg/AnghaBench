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
struct TYPE_3__ {scalar_t__ programObject; } ;
typedef  TYPE_1__ UserData ;
typedef  scalar_t__ GLuint ;
typedef  int GLint ;
typedef  char GLbyte ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 scalar_t__ LoadShader (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  glAttachShader (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  glBindAttribLocation (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 scalar_t__ glCreateProgram () ; 
 int /*<<< orphan*/  glDeleteProgram (scalar_t__) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (scalar_t__,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glLinkProgram (scalar_t__) ; 
 int /*<<< orphan*/  kdFree (char*) ; 
 int /*<<< orphan*/  kdLogMessage (char*) ; 
 char* kdMalloc (int) ; 

int Init ( UserData *userData )
{
   GLbyte vShaderStr[] =  
      "attribute vec4 vPosition;    \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = vPosition;  \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;\n"\
      "void main()                                  \n"
      "{                                            \n"
      "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
      "}                                            \n";

   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
   fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );

   // Create the program object
   programObject = glCreateProgram ( );
   
   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

   // Bind vPosition to attribute 0   
   glBindAttribLocation ( programObject, 0, "vPosition" );

   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked ) 
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog = kdMalloc (sizeof(char) * infoLen );

         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         kdLogMessage ( infoLog );
         
         kdFree ( infoLog );
      }

      glDeleteProgram ( programObject );
      return FALSE;
   }

   // Store the program object
   userData->programObject = programObject;

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return TRUE;
}