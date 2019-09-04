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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;
typedef  char GLbyte ;

/* Variables and functions */
 int GL_FALSE ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  LoadShader (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glAttachShader (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindAttribLocation (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 scalar_t__ glCreateProgram () ; 
 int /*<<< orphan*/  glDeleteProgram (scalar_t__) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (scalar_t__,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glLinkProgram (scalar_t__) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ programObject ; 

int Init ()
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
      "  gl_FragColor = vec4 ( 0.0, 0.0, 1.0, 1.0 );\n"
      "}                                            \n";

   GLuint vertexShader;
   GLuint fragmentShader;
   GLint linked;

   vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
   fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );

   programObject = glCreateProgram ( );
   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );
   glBindAttribLocation ( programObject, 0, "vPosition" );
   glLinkProgram ( programObject );
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );
   if ( !linked ) 
   {
      GLint infoLen = 0;
      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      if ( infoLen > 1 )
      {
         char* infoLog = malloc (sizeof(char) * infoLen );
         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         printf ( "Error linking program:\n%s\n", infoLog );            
         free ( infoLog );
      }
      glDeleteProgram ( programObject );
      return GL_FALSE;
   }

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}